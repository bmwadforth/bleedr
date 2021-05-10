#pragma once

#include <pcap.h>

// Packet handler
void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);

