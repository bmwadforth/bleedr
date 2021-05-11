#include <nlohmann/json.hpp>
#include <utility>
#include <string>
#include <sstream>
#include <filesystem>
#include "io/json_writer.h"
#include "wrappers.h"
#include "common/helpers.h"
#include "transport_layer/udp.h"

using namespace nlohmann;
using namespace Bleedr::IO;

void
json_writer_bridge() {
    jsonWriter->Write();
}

JsonWriter::JsonWriter(std::string filename, Bleedr_t *bleedr, bool with_raw) {
    this->with_raw = with_raw;
    this->filename = std::move(filename);
    this->bleedr = bleedr;
    this->offset = 0;
}

unsigned long long JsonWriter::Filesize() const {
    if (std::filesystem::exists(this->filename)) {
        return std::filesystem::file_size(this->filename);
    } else {
        return 0;
    }
}

json JsonWriter::Read() const {
    std::ifstream i(this->filename);
    json j;
    i >> j;
    return j;
}

void JsonWriter::Write() {
    json json_pkt_obj;

    switch (this->bleedr->lnk_lyr) {
        case ETHERNET:
            json_pkt_obj["link_layer"] = this->WithEthernet();
            break;
        case WIFI:
            json_pkt_obj["link_layer"] = this->WithWiFi();
            break;
        case ARP:
        case L2TP:
        default:
            break;
    }

    switch (this->bleedr->net_lyr) {
        case IPV4:
            json_pkt_obj["network_layer"] = this->WithIPv4();
            break;
        case IPV6:
            json_pkt_obj["network_layer"] = this->WithIPv6();
            break;
        default:
            break;
    }

    switch (this->bleedr->tpt_lyr) {
        case TCP:
            json_pkt_obj["transport_layer"] = this->WithTCP();
            break;
        case UDP:
            json_pkt_obj["transport_layer"] = this->WithUDP();
        default:
            break;
    }

    if (this->with_raw) {
        json_pkt_obj["raw"] = to_hex((uint8_t *) this->bleedr->packet_data, this->bleedr->packet_len);;
    }

    json_pkt_obj["link_layer"]["protocol"] = this->bleedr->lnk_lyr;
    json_pkt_obj["network_layer"]["protocol"] = this->bleedr->net_lyr;
    json_pkt_obj["transport_layer"]["protocol"] = this->bleedr->tpt_lyr;

    std::string serialized_string;

    if (this->Filesize() == 0) {
        json root_json;
        root_json["data"] = json::array();
        root_json["data"].push_back(json_pkt_obj);
        serialized_string = root_json.dump();
    } else {
        auto parsed_json = this->Read();
        // TODO Make sure data actually exists
        parsed_json["data"].push_back(json_pkt_obj);
        serialized_string = parsed_json.dump();
    }

    this->write_file.open(this->filename);
    this->write_file << serialized_string << std::endl;
    this->write_file.close();
}

json JsonWriter::WithEthernet() {
    auto *eth = (Ethernet_t *) this->bleedr->packet_data;
    this->offset += sizeof(Ethernet_t);

    std::string ether_type = to_hex((uint8_t *) eth->ether_type,
                                    sizeof(eth->ether_type), true);
    std::string destination_mac = to_mac(eth->dst_mac);
    std::string source_mac = to_mac(eth->src_mac);

    json tmp;
    tmp["meta"]["ether_type"] = ether_type;
    tmp["meta"]["source_mac"] = source_mac;
    tmp["meta"]["destination_mac"] = destination_mac;

    return tmp;
}

json JsonWriter::WithWiFi() {
    json tmp;

    return tmp;
}

json JsonWriter::WithIPv4() {
    auto *ip = (IPV4_t *) &this->bleedr->packet_data[this->offset];
    this->offset += sizeof(IPV4_t);

    std::string ip_protocol = to_hex((uint8_t *) ip->protocol, sizeof(ip->protocol), true);
    std::string ip_source = to_ipv4(ip->source_ip);
    std::string ip_destination = to_ipv4(ip->destination_ip);

    json tmp;
    tmp["meta"]["source_ip"] = ip_source;
    tmp["meta"]["destination_ip"] = ip_destination;

    return tmp;
}

json JsonWriter::WithIPv6() {
    json tmp;

    return tmp;
}

json JsonWriter::WithTCP() {
    auto *tcp = (TCP_packet *) &this->bleedr->packet_data[this->offset];
    this->offset += sizeof(TCP_packet);

    std::string tcp_destination_port = to_decimal(tcp->destination_port,
                                                  sizeof(tcp->destination_port));
    std::string tcp_source_port = to_decimal(tcp->source_port, sizeof(tcp->source_port));
    std::string sequence_num = to_decimal(tcp->sequence_number, sizeof(tcp->sequence_number));
    bool fin_flag = (bool) tcp->fin_flag;
    bool ack_flag = (bool) tcp->ack_flag;
    bool syn_flag = (bool) tcp->syn_flag;

    json tmp;
    tmp["meta"]["source_port"] = tcp_source_port;
    tmp["meta"]["destination_port"] = tcp_destination_port;
    tmp["meta"]["ack_flag"] = ack_flag;
    tmp["meta"]["fin_flag"] = fin_flag;
    tmp["meta"]["syn_flag"] = syn_flag;
    tmp["meta"]["sequence_number"] = sequence_num;

    return tmp;
}

json JsonWriter::WithUDP() {
    auto *udp = (UDP_packet *) &this->bleedr->packet_data[this->offset];
    this->offset += sizeof(UDP_packet);

    std::string udp_destination_port = to_decimal(udp->destination_port,
                                                  sizeof(udp->destination_port));
    std::string udp_source_port = to_decimal(udp->source_port, sizeof(udp->source_port));
    std::string udp_length = to_decimal(udp->length, sizeof(udp->length));
    std::string udp_checksum = to_hex(udp->checksum, sizeof(udp->checksum));

    json tmp;
    tmp["meta"]["source_port"] = udp_destination_port;
    tmp["meta"]["destination_port"] = udp_source_port;
    tmp["meta"]["length"] = udp_length;
    tmp["meta"]["checksum"] = udp_checksum;

    return tmp;
}
