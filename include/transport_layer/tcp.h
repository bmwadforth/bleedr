#ifndef BLEEDR_TCP_H
#define BLEEDR_TCP_H

#include "../types.h"
#include "../link_layer/ethernet.h"
#include "../network_layer/ip.h"

struct TCP_packet {
    unsigned char source_port[2];
    unsigned char destination_port[2];

    unsigned char sequence_number[4];
    unsigned char ack_number[4];

    unsigned char ns_flag: 1;
    unsigned char reserved: 3;
    unsigned char data_offset: 4;

    unsigned char fin_flag: 1;
    unsigned char syn_flag: 1;
    unsigned char rst_flag: 1;
    unsigned char psh_flag: 1;
    unsigned char ack_flag: 1;
    unsigned char urg_flag: 1;
    unsigned char ece_flag: 1;
    unsigned char cwr_flag: 1;
    unsigned char window_size[2];

    unsigned char checksum[2];
    unsigned char urgent_pointer[2];
};

typedef struct TCP_packet TCP_packet_t;

void handle_tcp(Ethernet_packet_t *, IPV4_packet_t *, Bleedr_t *);

#endif //BLEEDR_TCP_H
