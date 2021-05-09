#include "../../include/json_writer.h"
#include "../../include/wrappers.h"


void json_writer_bridge(char* buff, char* filename) {
    auto writer = new JsonWriter(filename);
}

JsonWriter::JsonWriter(std::string filename) {
    this->filename = filename;
    std::cout << "Filename: " << filename << std::endl;
}