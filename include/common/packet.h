#ifndef BLEEDR_PACKET_H
#define BLEEDR_PACKET_H

#include <pcap.h>

// Packet handler
void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);

#endif //BLEEDR_PACKET_H
