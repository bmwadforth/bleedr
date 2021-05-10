#include <stdio.h>
#include "../../include/types.h"
#include "../../../include/link_layer/ethernet.h"
#include "../../../include/network_layer/ip.h"

/*
 * This file handles 802.3 frames.
 * See: https://en.wikipedia.org/wiki/Ethernet_frame
 */

void handle_ethernet(Bleedr_t *bleedr) {
    Ethernet_t *eth_hdr = (Ethernet_t *) bleedr->packet_data;

    char *hex_eth_hd = malloc(sizeof(char) * 5);
    sprintf(hex_eth_hd, "%02X%02X", eth_hdr->ether_type[0], eth_hdr->ether_type[1]);
    long ether_type_decimal = strtol((const char *) hex_eth_hd, NULL, 16);
    free(hex_eth_hd);

    switch (ether_type_decimal) {
        case ETHERTYPE_IPV4:
            handle_ipv4(eth_hdr, bleedr);
            break;
        case ETHERTYPE_IPV6:
        case ETHERTYPE_8021X:
        case ETHERTYPE_ARP:
        case ETHERTYPE_8021Q:
        case ETHERTYPE_8021Q_NNI:
            fprintf(stderr, "EtherTypes IPV6, 802.1x, ARP, 802.1q/802.1q_nni are currently unsupported.\n");
            break;
    }
}