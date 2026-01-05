/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Socket operations
 */

#ifndef NSN_NETWORK_SOCKET_H
#define NSN_NETWORK_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* Create a new generic socket object (TCP or UDP) */
nsn_object *nsn_socket_new(int domain, int type, int protocol);

/* Bind the socket to a local address and port */
int nsn_socket_bind(nsn_object *sock, const char *host, int port);

/* Set socket to listen mode (for TCP servers) */
int nsn_socket_listen(nsn_object *sock, int backlog);

/* Accept a new connection (TCP only). Returns a new socket object. */
nsn_object *nsn_socket_accept(nsn_object *sock);

/* Connect the socket to a remote host (TCP client) */
int nsn_socket_connect(nsn_object *sock, const char *host, int port);

/* Close the socket and release resources */
int nsn_socket_close(nsn_object *sock);

/* Send data over the socket */
ssize_t nsn_socket_send(nsn_object *sock, const void *buf, size_t len, int flags);

/* Receive data from the socket */
ssize_t nsn_socket_recv(nsn_object *sock, void *buf, size_t len, int flags);

#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_SOCKET_H
