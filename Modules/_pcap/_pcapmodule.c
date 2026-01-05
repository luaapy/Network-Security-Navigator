#include "nsn.h"
#ifdef HAVE_LIBPCAP
#include <pcap.h>
#endif

/*
 * NSN Packet Capture Module (C Extension)
 * Wrapper for libpcap
 */

static nsn_object *pcap_open(nsn_object *self, nsn_object *args) {
#ifdef HAVE_LIBPCAP
    // pcap_open_live logic
#endif
    return NULL;
}

static nsn_object *pcap_next(nsn_object *self, nsn_object *args) {
    return NULL;
}

void _nsn_init_pcap(void) {
    /* Register PCAP methods */
}
