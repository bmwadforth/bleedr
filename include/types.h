#ifndef BLEEDR_TYPES_H
#define BLEEDR_TYPES_H

#include <pcap.h>

struct Bleedr {
    pcap_t *pcap_h;
    pcap_dumper_t *pcap_dump_h;
    const u_char *packet_data;
    int packet_len;
};

typedef struct Bleedr Bleedr_t;

// Packet handler
void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);

#endif //BLEEDR_TYPES_H
