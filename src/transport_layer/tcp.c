#include "types.h"
#include "transport_layer/tcp.h"

/*
 * This file handles TCP Datagrams.
 * See: https://en.wikipedia.org/wiki/Transmission_Control_Protocol
 */

void handle_tcp(Ethernet_t *eth_packet, IPV4_t *ipv4_packet, Bleedr_t *bleedr) {
    TCP_t *tcp_packet = (TCP_t *) &bleedr->packet_data[sizeof(Ethernet_t) + sizeof(IPV4_t)];

    // TODO: Figure out basics of what application protocol is in TCP payload
}