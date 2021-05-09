#ifndef BLEEDR_IPV4_H
#define BLEEDR_IPV4_H

#include "../types.h"
#include "../link_layer/ethernet.h"

// See https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers for protocol numbers.
// This is the list of protocols that are encapsulated by IP packets and are currently supported by bleedr.
#define IP_PROTOCOL_ICMP 0x01
#define IP_PROTOCOL_TCP 0x06
#define IP_PROTOCOL_EGP 0x08
#define IP_PROTOCOL_IGP 0x09
#define IP_PROTOCOL_UDP 0x11
#define IP_PROTOCOL_L2TP 0x73


struct IPV4_packet {
    unsigned char ihl: 4;
    unsigned char version: 4;

    unsigned char ecn: 2;
    unsigned char dscp: 6;

    unsigned char total_length[2];

    unsigned char identification[2];

    unsigned char fragment_offset[1];
    unsigned char fragment_offset_lower: 5;
    unsigned char flags: 3;

    unsigned char ttl[1];
    unsigned char protocol[1];
    unsigned char header_checksum[2];

    unsigned char source_ip[4];
    unsigned char destination_ip[4];

    // TODO: If ihl > 5 then options will be set on struct
};

typedef struct IPV4_packet IPV4_packet_t;

/*
struct IPV6_packet {

};

typedef struct IPV6_Packet IPV6_packet_t;*/

void handle_ipv4(Ethernet_packet_t *, Bleedr_t *);
void handle_ipv6();

#endif //BLEEDR_IPV4_H
