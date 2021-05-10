#pragma once

#include "tcp.h"

struct UDP_packet {
    uint8_t source_port[2];
    uint8_t destination_port[2];
    uint8_t length[2];
    uint8_t checksum[2];
};

typedef struct UDP_packet UDP_t;

void handle_udp(Ethernet_t *, IPV4_t *, Bleedr_t *);
