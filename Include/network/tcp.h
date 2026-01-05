/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * TCP protocol
 */

#ifndef NSN_NETWORK_TCP_H
#define NSN_NETWORK_TCP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* Create a new TCP socket object */
nsn_object *nsn_tcp_new(void);

/* Connect the TCP socket to a remote host */
int nsn_tcp_connect(nsn_object *tcp, const char *host, int port);

/* Send data over a connected TCP socket */
ssize_t nsn_tcp_send(nsn_object *tcp, const void *buf, size_t len, int flags);

/* Receive data from a connected TCP socket */
ssize_t nsn_tcp_recv(nsn_object *tcp, void *buf, size_t len, int flags);

/* Close the TCP socket */
int nsn_tcp_close(nsn_object *tcp);

#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_TCP_H
