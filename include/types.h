#ifndef BLEEDR_TYPES_H
#define BLEEDR_TYPES_H

#include <pcap.h>
#include <time.h>

struct Bleedr {
    pcap_t *pcap_h;
    pcap_dumper_t *pcap_dump_h;
    const uint8_t *packet_data;
    struct timeval packet_time;
    int packet_len;
};

typedef struct Bleedr Bleedr_t;

#endif //BLEEDR_TYPES_H
