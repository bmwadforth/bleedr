#pragma once

#include "../types.h"
#include "../link_layer/ethernet.h"
#include "../network_layer/ip.h"

struct TCP_packet {
    uint8_t source_port[2];
    uint8_t destination_port[2];
    uint8_t sequence_number[4];
    uint8_t ack_number[4];
    uint8_t ns_flag: 1;
    uint8_t reserved: 3;
    uint8_t data_offset: 4;
    uint8_t fin_flag: 1;
    uint8_t syn_flag: 1;
    uint8_t rst_flag: 1;
    uint8_t psh_flag: 1;
    uint8_t ack_flag: 1;
    uint8_t urg_flag: 1;
    uint8_t ece_flag: 1;
    uint8_t cwr_flag: 1;
    uint8_t window_size[2];
    uint8_t checksum[2];
    uint8_t urgent_pointer[2];
};

typedef struct TCP_packet TCP_t;

void handle_tcp(Ethernet_t *, IPV4_t *, Bleedr_t *);
