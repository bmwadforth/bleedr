#include <stdio.h>
#include <pcap.h>
#include <time.h>

#define scanf_s scanf

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
    struct tm *ltime;
    char timestr[16];
    time_t local_tv_sec;

    pcap_dump(param, header, pkt_data);

    /* convert the timestamp to readable format */
    local_tv_sec = header->ts.tv_sec;
    ltime=localtime(&local_tv_sec);
    strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);

    printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);

    for(int i = 0; i < header->len; i++) {
        printf("%d ", *pkt_data++);
    }

    printf("\n\n");
}

int main(int argc, char *argv[]) {
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
        fprintf(stderr, "Error: %s\n", errbuf);
        return(2);
    }

    pcap_t *pcapH = pcap_create(temp->name, errbuf);

    if (pcapH == NULL) {
        fprintf(stderr, "Error: %s\n", errbuf);
        return(2);
    }

    pcap_set_buffer_size(pcapH, 65536);
    pcap_set_snaplen(pcapH, 65535);

    // TODO: if pcap_activate fails, call pcap_close
    pcap_activate(pcapH);

    // TODO: switch datalinkType to determine how to deconstruct the packet
    int datalinkType = pcap_datalink(pcapH);

    pcap_dumper_t *dumpfile = pcap_dump_open(pcapH, "mydump.pcap");

    if(dumpfile == NULL)
    {
        fprintf(stderr,"\nError opening output file\n");
        return -1;
    }

    pcap_loop(pcapH, 0, packet_handler, (unsigned char *)dumpfile);
    return (0);
}