#ifndef BLEEDR_INTERFACE_H
#define BLEEDR_INTERFACE_H

#include <pcap.h>

// For link types see: https://www.tcpdump.org/linktypes.html
#define LINKTYPE_ETHERNET 0x1
#define LINKTYPE_WIFI 0x69

// Interface helpers
void get_interface(char[], pcap_if_t *);

void activate_interface(pcap_t *);

#endif //BLEEDR_INTERFACE_H
