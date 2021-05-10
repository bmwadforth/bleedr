#include "../../include/types.h"
#include "../../include/transport_layer/tcp.h"
#include "../../include/wrappers.h"


void handle_tcp(Ethernet_t *eth_packet, IPV4_t *ipv4_packet, Bleedr_t *bleedr) {
    TCP_t *tcp_packet = (TCP_t *) &bleedr->packet_data[sizeof(Ethernet_t) + sizeof(IPV4_t)];

    json_writer_bridge(eth_packet, ipv4_packet, tcp_packet, bleedr, "my_json.json");
}