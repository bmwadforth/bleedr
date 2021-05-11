#include <stdio.h>
#include <pcap.h>
#include "types.h"
#include "common/interface.h"
#include "link_layer/ethernet.h"
#include "link_layer/wifi.h"
#include "wrappers.h"

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    Bleedr_t *bleedr = (Bleedr_t *) param;

    pcap_dump((u_char *) bleedr->pcap_dump_h, header, pkt_data);

    int pcap_link_type = pcap_datalink(bleedr->pcap_h);
    if (pcap_link_type == PCAP_ERROR_NOT_ACTIVATED) {
        fprintf(stderr, "Attempting to get link type from handle that has not been activated");
    }

    bleedr->packet_len = header->len;
    bleedr->packet_data = pkt_data;
    bleedr->packet_time = header->ts;

    switch (pcap_link_type) {
        case L2TYPE_ETHERNET:
            bleedr->lnk_lyr = ETHERNET;
            handle_ethernet(bleedr);
            break;
        case L2TYPE_WIFI:
            bleedr->lnk_lyr = WIFI;
            handle_wifi(bleedr);
            break;
        default:
            //TODO: return pcap_error here, link-type encapsulating packet is not supported
            break;
    }

    json_writer_bridge();
}