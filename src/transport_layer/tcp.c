#include <stdio.h>
#include <stdlib.h>
#include "../../include/types.h"
#include "../../include/transport_layer/tcp.h"


void handle_tcp(Ethernet_packet_t *eth_packet, IPV4_packet_t *ipv4_packet, Bleedr_t *bleedr) {
    int x = sizeof(*eth_packet) + sizeof(*ipv4_packet);
    TCP_packet_t *tcp_packet = (TCP_packet_t *) &bleedr->packet_data[sizeof(Ethernet_packet_t) + sizeof(IPV4_packet_t)];

    printf("TCP Source Port: %X %X \n", tcp_packet->source_port[0], tcp_packet->source_port[1]);
    printf("TCP Destination Port: %X %X \n", tcp_packet->destination_port[0], tcp_packet->destination_port[1]);

}