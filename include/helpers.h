#ifndef BLEEDR_HELPERS_H
#define BLEEDR_HELPERS_H

#include <string>

std::string to_hex(uint8_t *, int, bool = false);

std::string to_mac(uint8_t *);

std::string to_ipv4(uint8_t *);

#endif //BLEEDR_HELPERS_H
