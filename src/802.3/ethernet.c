#include <stdio.h>
#include <string.h>
#include "../../include/types.h"

void handle_ethernet(Bleedr_t *bleedr) {
    char destination_mac[6] = "";
    char source_mac[6] = "";

    //const u_char *tmp = NULL;
    //memcpy((void*) tmp, bleedr->packet_data, bleedr->snap_len);

    memcpy(bleedr->destination_mac, bleedr->packet_data, 6);
    bleedr->destination_mac[9] = '\0';
    memcpy(bleedr->source_mac, bleedr->packet_data + 6, 6);
    bleedr->source_mac[9] = '\0';

    for (int i = 0; i < bleedr->snap_len; i++) {
        //printf("%X ", *bleedr->packet_data);
        bleedr->packet_data++;
    }

    printf("Destination Mac: %d", *bleedr->destination_mac);


    printf("\n\n");

}