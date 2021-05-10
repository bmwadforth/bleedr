#include <string>
#include <ios>
#include <iomanip>
#include <sstream>
#include "common/helpers.h"

std::string to_hex(uint8_t *buff, int len, bool with_prefix) {
    std::stringstream raw;
    raw << std::hex << std::setfill('0');
    for (int i = 0; i < len; ++i) {
        raw << std::setw(2) << static_cast<unsigned>(buff[i]);
    }

    if (with_prefix) {
        return "0x" + raw.str();
    } else {
        return raw.str();
    }
}

std::string to_mac(uint8_t *buff) {
    std::stringstream raw;

    for (int i = 0; i < 6; ++i) {
        if (i == 5) {
            raw << std::hex << (int) buff[i];
        } else {
            raw << std::hex << (int) buff[i] << ":";
        }
    }

    return raw.str();
}

std::string to_ipv4(uint8_t *buff) {
    std::stringstream raw;

    for (int i = 0; i < 4; ++i) {
        if (i == 3) {
            raw << (int) buff[i];
        } else {
            raw << (int) buff[i] << ".";
        }
    }

    return raw.str();
}

std::string to_decimal(uint8_t *buff, int len) {
    std::stringstream raw;
    unsigned int temp;

    std::string hex_val = to_hex(buff, len);
    raw << std::hex << hex_val;
    raw >> temp;
    raw << static_cast<int>(temp);

    return std::to_string(temp);
};