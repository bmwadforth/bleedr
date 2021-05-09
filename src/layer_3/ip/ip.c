#include <stdio.h>
#include <stdlib.h>
#include "../../../include/layer_3/ip.h"


void handle_ipv4(IPV4_packet_t *ipv4_packet) {
    IPV4_packet_t stack_var = *ipv4_packet;

    printf("IP Version: %X \n", stack_var.version);
    printf("IP IHL: %X \n", stack_var.ihl);

    printf("IP ECN: %X \n", stack_var.ecn);
    printf("IP DSCP: %X \n", stack_var.dscp);

    printf("IP Total Length: %X %X \n", stack_var.total_length[0], stack_var.total_length[1]);

    printf("IP Identification: %X %X \n", stack_var.identification[0], stack_var.identification[1]);
    printf("IP Fragment offset: %X \n", stack_var.fragment_offset[0]);
    printf("IP Fragment offset 2: %X \n", stack_var.fragment_offset_lower);

    printf("IP Flags: %X \n", stack_var.flags);

    printf("IP TTL: %X \n", stack_var.ttl[0]);
    printf("IP Protocol: %X \n", stack_var.protocol[0]);
    printf("IP Header Checksum: %X %X \n", stack_var.header_checksum[0], stack_var.header_checksum[1]);


    printf("IP Source IP: %d.%d.%d.%d \n", stack_var.source_ip[0], stack_var.source_ip[1], stack_var.source_ip[2], stack_var.source_ip[3]);
    printf("IP Destination IP: %d.%d.%d.%d \n", stack_var.destination_ip[0], stack_var.destination_ip[1], stack_var.destination_ip[2], stack_var.destination_ip[3]);

    printf("\n");

    char *ip_protocol = malloc(sizeof(char) * 3);
    sprintf(ip_protocol, "%02X", stack_var.protocol[0]);
    long ip_protocol_decimal = strtol((const char *) ip_protocol, NULL, 16);
    free(ip_protocol);

    switch(ip_protocol_decimal) {
        case IP_PROTOCOL_TCP:
            printf("IP Protocol is TCP \n");
            break;
        case IP_PROTOCOL_UDP:
            printf("IP Protocol is UDP \n");
            break;
        case IP_PROTOCOL_L2TP:
            printf("IP Protocol is L2TP \n");
            break;
    }
}