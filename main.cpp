#include <stdio.h>
#include <pcap.h>
#include <time.h>
#include "include/types.h"
#include "include/ethernet.h"
#include "include/wifi.h"

#define scanf_s scanf

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    struct tm *ltime;
    char timestr[16];
    time_t local_tv_sec;

    Bleedr_t *bleedr = (Bleedr_t *) param;

    pcap_dump((u_char *) bleedr->pcap_dumper_handle, header, pkt_data);

    /* convert the timestamp to readable format */
    local_tv_sec = header->ts.tv_sec;
    ltime = localtime(&local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

    /*printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);

    for (int i = 0; i < header->len; i++) {
        printf("%d ", *pkt_data++);
    }

    printf("\n\n");*/

    int pcap_link_type = pcap_datalink(bleedr->pcap_handle);
    if (pcap_link_type == PCAP_ERROR_NOT_ACTIVATED) {
        fprintf(stderr, "Attempting to get link type from handle that has not been activated");
    }

    bleedr->snap_len = header->len;
    bleedr->packet_data = pkt_data;
    bleedr->destination_mac = malloc(sizeof(char) * 10);
    bleedr->source_mac = malloc(sizeof(char) * 10);

    // For link types see: https://www.tcpdump.org/linktypes.html
    switch (pcap_link_type) {
        case 1:
            handle_ethernet(bleedr);
            break;
        case 105:
            //handle_wifi(bleedr);
            break;
        default:
            //TODO: return pcap_error here, link-type encapsulating packet is not supported
            break;
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_if_t *interfaces, *temp;
    int i = 0;
    if (pcap_findalldevs(&interfaces, errbuf) == -1) {
        fprintf(stderr, "Error: %s\n", errbuf);
        return (2);
    }

    for (temp = interfaces; temp; temp = temp->next) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        printf("\n%d) %s", i++, temp->description);
#else
        printf("\n%d) %s", i++, temp->name);
#endif

    }

    printf("\n\nSelect interface: ");
    int iface;
    scanf_s("%d", &iface);

    i = 0;
    for (temp = interfaces; temp; temp = temp->next) {
        if (i == iface) {
            break;
        }
        i++;
    }

    if (pcap_init(PCAP_CHAR_ENC_UTF_8, errbuf) == -1) {
        fprintf(stderr, "Initialise Error: %s\n", errbuf);
        return (2);
    }

    pcap_t *pcap_h = pcap_create(temp->name, errbuf);
    if (pcap_h == NULL) {
        fprintf(stderr, "Create Error: %s\n", errbuf);
        return (2);
    }

    pcap_set_buffer_size(pcap_h, 65536);
    pcap_set_snaplen(pcap_h, 65535);

    int activateErr = pcap_activate(pcap_h);
    if (activateErr < 0) {
        fprintf(stderr, "Activate Error: %d\n", activateErr);
        return (2);
    }

    pcap_dumper_t *pcap_dump_handle = pcap_dump_open(pcap_h, "mydump.pcap");

    if (pcap_dump_handle == NULL) {
        fprintf(stderr, "Error Opening Dump\n");
        return (2);
    }


    Bleedr_t *bleedr = (Bleedr_t*) malloc(sizeof *bleedr);
    bleedr->pcap_handle = pcap_h;
    bleedr->pcap_dumper_handle = pcap_dump_handle;

    pcap_loop(pcap_h, 0, packet_handler, (unsigned char *) bleedr);
    return (0);
}