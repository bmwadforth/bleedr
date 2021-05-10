#ifndef BLEEDR_JSON_WRITER_H
#define BLEEDR_JSON_WRITER_H

#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "types.h"
#include "link_layer/ethernet.h"
#include "network_layer/ip.h"
#include "transport_layer/tcp.h"

using namespace nlohmann;

class JsonWriter {
private:
    std::ifstream read_file;
    std::ofstream write_file;
    Ethernet_packet_t *ethernet_packet;
    IPV4_packet_t *ip_packet;
    TCP_packet_t *tcp_packet;
    Bleedr_t *bleedr;
public:
    std::string filename;

    JsonWriter(Ethernet_packet_t *, IPV4_packet_t *, TCP_packet_t *, Bleedr_t *, std::string);

    json Read() const;

    void Write();

    long Filesize() const;
};


#endif //BLEEDR_JSON_WRITER_H
