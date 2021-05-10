#pragma once

// See https://en.wikipedia.org/wiki/EtherType for ether types.
#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_IPV6 0x86DD
#define ETHERTYPE_8021Q 0x9100
#define ETHERTYPE_8021Q_NNI 0x8100
#define ETHERTYPE_8021X 0x888E
#define ETHERTYPE_ARP 0x0806

struct Ethernet_packet {
    uint8_t dst_mac[6];
    uint8_t src_mac[6];
    uint8_t ether_type[2];
};

typedef struct Ethernet_packet Ethernet_t;

void handle_ethernet(Bleedr_t *bleedr);
