#include <stdio.h>
#include <stdlib.h>
#include "network_layer/ip.h"
#include "transport_layer/tcp.h"

/*
 * This file handles IPV4 Packets.
 * See: https://en.wikipedia.org/wiki/IPv4
 */

void handle_ipv4(Ethernet_t *eth_packet, Bleedr_t *bleedr) {
    IPV4_t *ip_packet = (IPV4_t *) &bleedr->packet_data[sizeof(Ethernet_t)];

    char *ip_protocol = malloc(sizeof(char) * 3);
    sprintf(ip_protocol, "%02X", ip_packet->protocol[0]);
    long ip_protocol_decimal = strtol((const char *) ip_protocol, NULL, 16);
    free(ip_protocol);

    switch (ip_protocol_decimal) {
        case IP_PROTOCOL_TCP:
            bleedr->tpt_lyr = TCP;
            handle_tcp(eth_packet, ip_packet, bleedr);
            break;
        case IP_PROTOCOL_UDP:
        case IP_PROTOCOL_L2TP:
            fprintf(stderr, "IP Protocol L2TP, UDP are currently unsupported.\n");
            break;
    }
}