#ifndef BLEEDR_JSON_WRITER_H
#define BLEEDR_JSON_WRITER_H

#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../types.h"
#include "../link_layer/ethernet.h"
#include "../network_layer/ip.h"
#include "../transport_layer/tcp.h"

using namespace nlohmann;

class JsonWriter {
private:
    std::ofstream write_file;
    Ethernet_t *ethernet_packet;
    IPV4_t *ip_packet;
    TCP_t *tcp_packet;
    Bleedr_t *bleedr;
public:
    std::string filename;

    JsonWriter(Ethernet_t *, IPV4_t *, TCP_t *, Bleedr_t *, std::string);

    json Read() const;

    void Write();

    long Filesize() const;
};


#endif //BLEEDR_JSON_WRITER_H
