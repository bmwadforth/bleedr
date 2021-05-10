#include <nlohmann/json.hpp>
#include <utility>
#include <string>
#include <sstream>
#include <filesystem>
#include "../../include/io/json_writer.h"
#include "../../include/wrappers.h"
#include "../../include/helpers.h"

using namespace nlohmann;

void
json_writer_bridge(Ethernet_t *eth_packet, IPV4_t *ip_packet, TCP_t *tcp_packet, Bleedr_t *bleedr,
                   char *filename) {
    auto writer = new JsonWriter(eth_packet, ip_packet, tcp_packet, bleedr, filename);
    writer->Write();
    delete writer;
}

JsonWriter::JsonWriter(Ethernet_t *eth_packet, IPV4_t *ip_packet, TCP_t *tcp_packet,
                       Bleedr_t *bleedr,
                       std::string filename) {
    this->filename = std::move(filename);
    this->ethernet_packet = eth_packet;
    this->ip_packet = ip_packet;
    this->tcp_packet = tcp_packet;
    this->bleedr = bleedr;
}

long JsonWriter::Filesize() const {
    return std::filesystem::file_size(this->filename);
}

json JsonWriter::Read() const {
    std::ifstream i(this->filename);
    json j;
    i >> j;
    return j;
}

void JsonWriter::Write() {
    std::string ether_type = to_hex((uint8_t *) this->ethernet_packet->ether_type,
                                    sizeof(this->ethernet_packet->ether_type), true);
    std::string destination_mac = to_mac(this->ethernet_packet->dst_mac);
    std::string source_mac = to_mac(this->ethernet_packet->src_mac);
    std::string ip_protocol = to_hex((uint8_t *) this->ip_packet->protocol, sizeof(this->ip_packet->protocol), true);
    std::string ip_source = to_ipv4(this->ip_packet->source_ip);
    std::string ip_destination = to_ipv4(this->ip_packet->destination_ip);
    std::string tcp_destination_port = to_decimal(this->tcp_packet->destination_port,
                                                  sizeof(this->tcp_packet->destination_port));
    std::string tcp_source_port = to_decimal(this->tcp_packet->source_port, sizeof(this->tcp_packet->source_port));
    std::string raw_packet = to_hex((uint8_t *) this->bleedr->packet_data, this->bleedr->packet_len);

    json json_pkt_obj;
    json_pkt_obj["link_layer"] = {{"ether_type",      ether_type},
                                  {"source_mac",      source_mac},
                                  {"destination_mac", destination_mac}};
    json_pkt_obj["network_layer"] = {{"protocol",       ip_protocol},
                                     {"source_ip",      ip_source},
                                     {"destination_ip", ip_destination}};
    json_pkt_obj["transport_layer"] = {{"source_port",      tcp_source_port},
                                       {"destination_port", tcp_destination_port}};
    json_pkt_obj["raw"] = raw_packet;

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