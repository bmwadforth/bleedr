#include <stdio.h>
#include <pcap.h>

#define scanf_s scanf

void get_interface(char err_buf[], pcap_if_t *pcap_iface) {
    pcap_if_t *interfaces, *tmp;
    int i = 0;
    if (pcap_findalldevs(&interfaces, err_buf) == -1) {
        fprintf(stderr, "Error: %s\n", err_buf);
    }

    for (tmp = interfaces; tmp; tmp = tmp->next) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        printf("\n%d) %s", i++, tmp->description);
#else
        printf("\n%d) %s", i++, tmp->name);
#endif

    }

    printf("\n\nSelect interface: ");
    int iface;
    scanf_s("%d", &iface);

    i = 0;
    for (tmp = interfaces; tmp; tmp = tmp->next) {
        if (i == iface) {
            break;
        }
        i++;
    }

    *pcap_iface = *tmp;
    pcap_freealldevs(interfaces);
};

void activate_interface(pcap_t *pcap_h) {
    // Set packet capture settings
    pcap_set_buffer_size(pcap_h, 65536);
    pcap_set_snaplen(pcap_h, 65535);

    // Activate packet capture
    int activate_err = pcap_activate(pcap_h);
    if (activate_err < 0) {
        fprintf(stderr, "Activate Error: %d\n", activate_err);
    }
}