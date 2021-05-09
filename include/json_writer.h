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
public:
    std::string filename;
    JsonWriter(std::string filename);
};


#endif //BLEEDR_JSON_WRITER_H
