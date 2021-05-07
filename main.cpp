#include <cstdio>
#include <pcap.h>

extern "C" {
#include "include/types.h"
#include "include/ethernet.h"
#include "include/wifi.h"
}

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    auto *bleedr = (Bleedr_t *) param;

    pcap_dump((u_char *) bleedr->pcap_dumper_handle, header, pkt_data);

    int pcap_link_type = pcap_datalink(bleedr->pcap_handle);
    if (pcap_link_type == PCAP_ERROR_NOT_ACTIVATED) {
        fprintf(stderr, "Attempting to get link type from handle that has not been activated");
    }

    bleedr->packet_len = header->len;
    bleedr->packet_data = pkt_data;

    // For link types see: https://www.tcpdump.org/linktypes.html
    switch (pcap_link_type) {
        case 1:
            handle_ethernet(bleedr);
            break;
        case 105:
            handle_wifi(bleedr);
            break;
        default:
            //TODO: return pcap_error here, link-type encapsulating packet is not supported
            break;
    }
}

int main() {
    char err_buff[PCAP_ERRBUF_SIZE];

    auto *pcap_iface = (pcap_if_t *) malloc(sizeof(pcap_if_t *));
    get_interface(err_buff, pcap_iface);

    //auto *pcap_h = (pcap_t *) malloc(sizeof(pcap_t *));
    //activate_interface(err_buff, pcap_iface, pcap_h);

    if (pcap_init(PCAP_CHAR_ENC_UTF_8, err_buff) == -1) {
        fprintf(stderr, "Initialise Error: %s\n", err_buff);
    }

    pcap_t *pcap_h = pcap_create(pcap_iface->name, err_buff);
    if (pcap_h == NULL) {
        fprintf(stderr, "Create Error: %s\n", err_buff);
    }

    // Set packet capture settings
    pcap_set_buffer_size(pcap_h, 65536);
    pcap_set_snaplen(pcap_h, 65535);

    // Activate packet capture
    int activate_err = pcap_activate(pcap_h);
    if (activate_err < 0) {
        fprintf(stderr, "Activate Error: %d\n", activate_err);
    }


    pcap_dumper_t *pcap_dump_handle = pcap_dump_open(pcap_h, "mydump.pcap");
    if (pcap_dump_handle == nullptr) {
        fprintf(stderr, "Error Opening Dump\n");
        return (2);
    }


    auto *bleedr = (Bleedr_t *) malloc(sizeof(Bleedr_t *));
    bleedr->pcap_handle = pcap_h;
    bleedr->pcap_dumper_handle = pcap_dump_handle;

    pcap_loop(pcap_h, 0, packet_handler, (unsigned char *) bleedr);

    return (0);
}