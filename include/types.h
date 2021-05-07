#ifndef BLEEDR_TYPES_H
#define BLEEDR_TYPES_H

#include <pcap.h>

struct Bleedr {
    pcap_t *pcap_handle;
    pcap_dumper_t *pcap_dumper_handle;
    const u_char *packet_data;
    int snap_len;
    char *destination_mac;
    char *source_mac;
};

typedef struct Bleedr Bleedr_t;

#endif //BLEEDR_TYPES_H
