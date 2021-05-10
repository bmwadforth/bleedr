#include "types.h"
#include "transport_layer/tcp.h"
#include "wrappers.h"

/*
 * This file handles TCP Datagrams.
 * See: https://en.wikipedia.org/wiki/Transmission_Control_Protocol
 */

void handle_tcp(Ethernet_t *eth_packet, IPV4_t *ipv4_packet, Bleedr_t *bleedr) {
    TCP_t *tcp_packet = (TCP_t *) &bleedr->packet_data[sizeof(Ethernet_t) + sizeof(IPV4_t)];

    json_writer_bridge();
}