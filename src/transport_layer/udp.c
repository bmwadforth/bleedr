#include "types.h"
#include "transport_layer/udp.h"

/*
 * This file handles UDP Datagrams.
 * See: https://en.wikipedia.org/wiki/User_Datagram_Protocol
 */

void handle_udp(Ethernet_t *eth_packet, IPV4_t *ipv4_packet, Bleedr_t *bleedr) {
    UDP_t *udp_packet = (UDP_t *) &bleedr->packet_data[sizeof(Ethernet_t) + sizeof(IPV4_t)];

    // TODO: Figure out basics of what application protocol is in TCP payload
}