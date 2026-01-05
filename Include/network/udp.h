/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * UDP protocol
 */

#ifndef NSN_NETWORK_UDP_H
#define NSN_NETWORK_UDP_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct {
    nsn_object base;
    int fd;
} nsn_udp_object;

nsn_object *nsn_udp_new(void);
int nsn_udp_send(nsn_object *udp, const char *host, int port, const char *data, size_t len);
int nsn_udp_recv(nsn_object *udp, char *buf, size_t len, char *from_host, int *from_port);


#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_UDP_H
