#include <nlohmann/json.hpp>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include "../../include/json_writer.h"
#include "../../include/wrappers.h"
#include "../../include/link_layer/ethernet.h"
#include "../../include/network_layer/ip.h"
#include "../../include/transport_layer/tcp.h"

using namespace nlohmann;

std::string hexStr(BYTE *data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return "0x" + ss.str();
}

void
json_writer_bridge(Ethernet_packet_t *eth_packet, IPV4_packet_t *ip_packet, TCP_packet_t *tcp_packet, char *filename) {
    auto writer = new JsonWriter(eth_packet, ip_packet, tcp_packet, filename);
    writer->Write();
}

JsonWriter::JsonWriter(Ethernet_packet_t *eth_packet, IPV4_packet_t *ip_packet, TCP_packet_t *tcp_packet,
                       std::string filename) {
    this->filename = std::move(filename);
    this->ethernet_packet = eth_packet;
    this->ip_packet = ip_packet;
    this->tcp_packet = tcp_packet;
}

void JsonWriter::Write() {
    this->file.open(this->filename);

    std::string ether_type = hexStr(this->ethernet_packet->ether_type, sizeof(this->ethernet_packet->ether_type));
    std::string destination_mac = hexStr(this->ethernet_packet->dst_mac, sizeof(this->ethernet_packet->dst_mac));
    std::string source_mac = hexStr(this->ethernet_packet->src_mac, sizeof(this->ethernet_packet->src_mac));

    std::string ip_protocol = hexStr(this->ip_packet->protocol, sizeof(this->ip_packet->protocol));
    std::string ip_source = hexStr(this->ip_packet->source_ip, sizeof(this->ip_packet->source_ip));
    std::string ip_destination = hexStr(this->ip_packet->destination_ip, sizeof(this->ip_packet->destination_ip));
    //std::string ip_version = hexStr(reinterpret_cast<BYTE *>(this->ip_packet->version), 1);

    // TODO: check if data array exists in file, if not
    json j;
    j = {
            {"packet",
                    {
                            {"link_layer", {
                                                   {"ether_type",  ether_type},
                                                   {"source_mac", source_mac},
                                                   {"destination_mac", destination_mac}
                                           }},
                            {"network_layer", {
                                                      //{"version", ip_version},
                                                      {"protocol", ip_protocol},
                                                      {"source_ip", ip_source},
                                                      {"destination_ip", ip_destination}
                                              }},
                            {"transport_layer", {

                                                }}
                    }
            },
    };

    std::string serialized_string = j.dump();

    // TODO: append this j object to an array then write to file

    this->file << serialized_string << std::endl;
    this->file.close();
}