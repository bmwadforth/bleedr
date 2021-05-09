#ifndef BLEEDR_JSON_WRITER_H
#define BLEEDR_JSON_WRITER_H

#include <iostream>
#include <string>
#include <fstream>
#include "types.h"
#include "link_layer/ethernet.h"
#include "network_layer/ip.h"
#include "transport_layer/tcp.h"

class JsonWriter {
private:
    std::ofstream file;
    Ethernet_packet_t *ethernet_packet;
    IPV4_packet_t *ip_packet;
    TCP_packet_t *tcp_packet;
public:
    std::string filename;

    JsonWriter(Ethernet_packet_t *, IPV4_packet_t *, TCP_packet_t *, std::string);

    void Write();
};


#endif //BLEEDR_JSON_WRITER_H
