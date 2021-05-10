#ifndef BLEEDR_TYPES_H
#define BLEEDR_TYPES_H

#include <pcap.h>
#include <time.h>

typedef enum LNK_LYR_PROTOCOL {
    ETHERNET,
    WIFI,
    ARP,
    L2TP
} LNK_LYR_PROTOCOL_T;

typedef enum NET_LYR_PROTOCOL {
    IPV4,
    IPV6
} NET_LYR_PROTOCOL_T;

typedef enum TPT_LYR_PROTOCOL {
    TCP,
    UDP
} TPT_LYR_PROTOCOL_T;

typedef struct Bleedr_ {
    pcap_t *pcap_h;
    pcap_dumper_t *pcap_dump_h;
    const uint8_t *packet_data;
    struct timeval packet_time;
    int packet_len;

    LNK_LYR_PROTOCOL_T lnk_lyr;
    NET_LYR_PROTOCOL_T net_lyr;
    TPT_LYR_PROTOCOL_T tpt_lyr;
} Bleedr_t;

#endif //BLEEDR_TYPES_H
