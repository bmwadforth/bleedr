#include <stdio.h>
#include "../../include/types.h"
#include "../../include/ethernet.h"


void handle_ethernet(Bleedr_t *bleedr) {
    Ethernet_header_t *eth_hdr = (Ethernet_header_t *) bleedr->packet_data;

    char *hex_eth_hd = malloc(sizeof(char) * 5);
    sprintf(hex_eth_hd, "%02X%02X", eth_hdr->ether_type[0], eth_hdr->ether_type[1]);
    long number = strtol((const char *)hex_eth_hd, NULL, 16);
    free(hex_eth_hd);

    switch(number) {
        case ETHERTYPE_IPV4:
        case ETHERTYPE_IPV6:
        case ETHERTYPE_8021X:
        case ETHERTYPE_ARP:
            //TODO: Calculate payload size
        case ETHERTYPE_8021Q:
            break;
        case ETHERTYPE_8021Q_NNI:
            break;
            break;
    }

    printf("\n\n");
}