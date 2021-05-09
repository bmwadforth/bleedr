#include <stdio.h>
#include <stdlib.h>
#include "../../include/network_layer/ip.h"
#include "../../include/transport_layer/tcp.h"


void handle_ipv4(Ethernet_packet_t *eth_packet, Bleedr_t *bleedr) {
    IPV4_packet_t *ip_packet = (IPV4_packet_t *) &bleedr->packet_data[sizeof(Ethernet_packet_t)];

    char *ip_protocol = malloc(sizeof(char) * 3);
    sprintf(ip_protocol, "%02X", ip_packet->protocol[0]);
    long ip_protocol_decimal = strtol((const char *) ip_protocol, NULL, 16);
    free(ip_protocol);

    printf("IP Version: %X \n", ip_packet->version);
    printf("IP IHL: %X \n", ip_packet->ihl);

    printf("IP ECN: %X \n", ip_packet->ecn);
    printf("IP DSCP: %X \n", ip_packet->dscp);

    printf("IP Total Length: %X %X \n", ip_packet->total_length[0], ip_packet->total_length[1]);

    printf("IP Identification: %X %X \n", ip_packet->identification[0], ip_packet->identification[1]);
    printf("IP Fragment offset: %X \n", ip_packet->fragment_offset[0]);
    printf("IP Fragment offset 2: %X \n", ip_packet->fragment_offset_lower);

    printf("IP Flags: %X \n", ip_packet->flags);

    printf("IP TTL: %X \n", ip_packet->ttl[0]);
    printf("IP Protocol: %X \n", ip_packet->protocol[0]);
    printf("IP Header Checksum: %X %X \n", ip_packet->header_checksum[0], ip_packet->header_checksum[1]);


    printf("IP Source IP: %d.%d.%d.%d \n", ip_packet->source_ip[0], ip_packet->source_ip[1], ip_packet->source_ip[2], ip_packet->source_ip[3]);
    printf("IP Destination IP: %d.%d.%d.%d \n", ip_packet->destination_ip[0], ip_packet->destination_ip[1], ip_packet->destination_ip[2], ip_packet->destination_ip[3]);

    printf("\n");

    switch(ip_protocol_decimal) {
        case IP_PROTOCOL_TCP:
            handle_tcp(eth_packet, ip_packet, bleedr);
            break;
        case IP_PROTOCOL_UDP:
            printf("IP Protocol is UDP \n");
            break;
        case IP_PROTOCOL_L2TP:
            printf("IP Protocol is L2TP \n");
            break;
    }
}