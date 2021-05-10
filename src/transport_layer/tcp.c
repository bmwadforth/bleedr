#include "../../include/types.h"
#include "../../include/transport_layer/tcp.h"
#include "../../include/wrappers.h"


void handle_tcp(Ethernet_packet_t *eth_packet, IPV4_packet_t *ipv4_packet, Bleedr_t *bleedr) {
    TCP_packet_t *tcp_packet = (TCP_packet_t *) &bleedr->packet_data[sizeof(Ethernet_packet_t) + sizeof(IPV4_packet_t)];

    json_writer_bridge(eth_packet, ipv4_packet, tcp_packet, bleedr, "my_json.json");
}