#pragma once

#include <string>

std::string to_hex(uint8_t *, int, bool = false);

std::string to_mac(uint8_t *);

std::string to_ipv4(uint8_t *);

std::string to_decimal(uint8_t *, int);

