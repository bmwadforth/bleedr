#include <stdio.h>
#include <stdlib.h>
#include "../../include/types.h"
#include "../../include/transport_layer/udp.h"
#include "../../include/link_layer/ethernet.h"
#include "../../include/network_layer/ip.h"


void handle_udp(Ethernet_packet_t *eth_packet, IPV4_packet_t *ipv4_packet, Bleedr_t *bleedr) {
    UDP_packet_t *udp_packet = (UDP_packet_t *) &bleedr->packet_data[sizeof(Ethernet_packet_t) + sizeof(IPV4_packet_t)];

    printf("UDP Source Port: %X %X \n", udp_packet->source_port[0], udp_packet->source_port[1]);
    printf("UDP Destination Port: %X %X \n", udp_packet->destination_port[0], udp_packet->destination_port[1]);

}