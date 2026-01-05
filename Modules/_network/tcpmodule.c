#include "nsn.h"
#include "network/tcp.h"
#include "network/socket.h"
#include <stdio.h>

/*
 * NSN TCP Module Implementation
 */

nsn_object *nsn_tcp_connect(const char *host, int port) {
    /* Use AF_INET (2), SOCK_STREAM (1), IPPROTO_TCP (6) */
    nsn_object *so = nsn_socket_new(2, 1, 6);
    if (nsn_socket_connect(so, host, port) != 0) {
        nsn_decref(so);
        return NULL;
    }
    return so;
}

nsn_object *nsn_tcp_listen(int port) {
    /* Implementation of TCP server listen */
    return NULL;
}
