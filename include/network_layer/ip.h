#ifndef BLEEDR_IP_H
#define BLEEDR_IP_H

#include "../types.h"
#include "../link_layer/ethernet.h"

// See https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers for protocol numbers.
#define IP_PROTOCOL_ICMP 0x01
#define IP_PROTOCOL_TCP 0x06
#define IP_PROTOCOL_EGP 0x08
#define IP_PROTOCOL_IGP 0x09
#define IP_PROTOCOL_UDP 0x11
#define IP_PROTOCOL_L2TP 0x73


struct IPV4_packet {
    uint8_t ihl: 4;
    uint8_t version: 4;
    uint8_t ecn: 2;
    uint8_t dscp: 6;
    uint8_t total_length[2];
    uint8_t identification[2];
    uint8_t fragment_offset[1];
    uint8_t fragment_offset_lower: 5;
    uint8_t flags: 3;
    uint8_t ttl[1];
    uint8_t protocol[1];
    uint8_t header_checksum[2];
    uint8_t source_ip[4];
    uint8_t destination_ip[4];
};

typedef struct IPV4_packet IPV4_t;

void handle_ipv4(Ethernet_t *, Bleedr_t *);
void handle_ipv6();

#endif //BLEEDR_IP_H
