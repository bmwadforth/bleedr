#ifndef BLEEDR_UDP_H
#define BLEEDR_UDP_H

#include "tcp.h"

struct UDP_packet {
    unsigned char source_port[2];
    unsigned char destination_port[2];

    unsigned char length[2];
    unsigned char checksum[2];
};

typedef struct UDP_packet UDP_packet_t;

void handle_udp(Ethernet_packet_t *, IPV4_packet_t *, Bleedr_t *);

#endif //BLEEDR_UDP_H
