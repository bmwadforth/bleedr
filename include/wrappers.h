#ifndef BLEEDR_WRAPPERS_H
#define BLEEDR_WRAPPERS_H

#include "link_layer/ethernet.h"
#include "network_layer/ip.h"
#include "transport_layer/tcp.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void json_writer_bridge(Ethernet_packet_t*, IPV4_packet_t*, TCP_packet_t*, char* filename);

#undef EXTERNC
// ...

#endif //BLEEDR_WRAPPERS_H
