#include <nlohmann/json.hpp>
#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include "../../include/json_writer.h"
#include "../../include/wrappers.h"
#include "../../include/helpers.h"
#include "../../include/link_layer/ethernet.h"
#include "../../include/network_layer/ip.h"
#include "../../include/transport_layer/tcp.h"

using namespace nlohmann;

void
json_writer_bridge(Ethernet_packet_t *eth_packet, IPV4_packet_t *ip_packet, TCP_packet_t *tcp_packet, Bleedr_t *bleedr,
                   char *filename) {
    auto writer = new JsonWriter(eth_packet, ip_packet, tcp_packet, bleedr, filename);
    writer->Write();
}

JsonWriter::JsonWriter(Ethernet_packet_t *eth_packet, IPV4_packet_t *ip_packet, TCP_packet_t *tcp_packet,
                       Bleedr_t *bleedr,
                       std::string filename) {
    this->filename = std::move(filename);
    this->ethernet_packet = eth_packet;
    this->ip_packet = ip_packet;
    this->tcp_packet = tcp_packet;
    this->bleedr = bleedr;
}

void JsonWriter::Write() {
    this->file.open(this->filename);

    std::string ether_type = to_hex((uint8_t *) this->ethernet_packet->ether_type,
                                    sizeof(this->ethernet_packet->ether_type), true);
    std::string destination_mac = to_mac(this->ethernet_packet->dst_mac);
    std::string source_mac = to_mac(this->ethernet_packet->src_mac);

    std::string ip_protocol = to_hex((uint8_t *) this->ip_packet->protocol, sizeof(this->ip_packet->protocol), true);
    std::string ip_source = to_ipv4(this->ip_packet->source_ip);
    std::string ip_destination = to_ipv4(this->ip_packet->destination_ip);

    std::string tcp_destination_port = to_decimal(this->tcp_packet->destination_port, sizeof(this->tcp_packet->destination_port));
    std::string tcp_source_port = to_decimal(this->tcp_packet->source_port, sizeof(this->tcp_packet->source_port));

    std::string raw_packet = to_hex((uint8_t *) this->bleedr->packet_data, this->bleedr->packet_len);


    // TODO: check if data array exists in file, if not
    json j;
    j = {
            {"packet",
                    {
                            {"link_layer", {
                                                   {"ether_type", ether_type},
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
                                                        {"source_port", tcp_source_port},
                                                        {"destination_port", tcp_destination_port},
                                                }},
                            {"raw", raw_packet}
                    },
            },
    };

    std::string serialized_string = j.dump();

    // TODO: append this j object to an array then write to file

    this->file << serialized_string << std::endl;
    this->file.close();
}