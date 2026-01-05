#include "nsn.h"
#include "network/udp.h"
#include "network/socket.h"
#include <stdio.h>

/*
 * NSN UDP Module Implementation
 */

nsn_object *nsn_udp_new_socket(void) {
    /* AF_INET (2), SOCK_DGRAM (2), IPPROTO_UDP (17) */
    return nsn_socket_new(2, 2, 17);
}

int nsn_udp_send_data(nsn_object *so, const char *host, int port, const char *data, size_t len) {
    /* Implementation of UDP sendto */
    return 0;
}
