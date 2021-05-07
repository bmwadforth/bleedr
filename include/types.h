#ifndef BLEEDR_TYPES_H
#define BLEEDR_TYPES_H

#include <pcap.h>

struct Bleedr {
    pcap_t *pcap_handle;
    pcap_dumper_t *pcap_dumper_handle;
    const u_char *packet_data;
    int packet_len;
};

typedef struct Bleedr Bleedr_t;

void get_interface(char[], pcap_if_t *);
void activate_interface(char[], pcap_if_t *, pcap_t *);

#endif //BLEEDR_TYPES_H
