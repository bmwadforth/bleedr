#include <stdio.h>
#include "../../include/types.h"

void handle_ethernet(Bleedr_t *bleedr) {
    for (int i = 0; i < bleedr->packet_len; i++) {
        printf("%X ", *bleedr->packet_data);
        bleedr->packet_data++;
    }
    printf("\n\n");
}