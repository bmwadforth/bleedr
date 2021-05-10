#pragma once

#include "link_layer/ethernet.h"
#include "network_layer/ip.h"
#include "transport_layer/tcp.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void json_writer_bridge();

#undef EXTERNC

