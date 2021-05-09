#ifndef BLEEDR_ETHERNET_H
#define BLEEDR_ETHERNET_H

#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_IPV6 0x86DD
#define ETHERTYPE_8021Q 0x9100
#define ETHERTYPE_8021Q_NNI 0x8100
#define ETHERTYPE_8021X 0x888E
#define ETHERTYPE_ARP 0x0806

struct Ethernet_packet {
    /* destination MAC */
    u_char dst_mac[6];
    /* source MAC */
    u_char src_mac[6];
    /* EtherType */
    // See https://en.wikipedia.org/wiki/EtherType for ether types.
    u_char ether_type[2];
};

typedef struct Ethernet_packet Ethernet_packet_t;

void handle_ethernet(Bleedr_t *bleedr);

#endif //BLEEDR_ETHERNET_H
