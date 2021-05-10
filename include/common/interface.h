#pragma once

#include <pcap.h>

// For link types see: https://www.tcpdump.org/linktypes.html
#define L2TYPE_ETHERNET 0x1
#define L2TYPE_WIFI 0x69

// Interface helpers
void get_interface(char[], pcap_if_t *);

void activate_interface(pcap_t *);
