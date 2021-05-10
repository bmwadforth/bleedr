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

EXTERNC void json_writer_bridge(Ethernet_t*, IPV4_t*, TCP_t*, Bleedr_t*, char* filename);

#undef EXTERNC
// ...

#endif //BLEEDR_WRAPPERS_H
