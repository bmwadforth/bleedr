#ifndef BLEEDR_INTERFACE_H
#define BLEEDR_INTERFACE_H

#include <pcap.h>

// Interface helpers
void get_interface(char[], pcap_if_t *);

void activate_interface(pcap_t *);

#endif //BLEEDR_INTERFACE_H
