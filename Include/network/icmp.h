/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * ICMP protocol
 */

#ifndef NSN_NETWORK_ICMP_H
#define NSN_NETWORK_ICMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* Create a new ICMP socket object */
nsn_object *nsn_icmp_new(void);

/* Send an ICMP echo request (ping) to the given host. timeout_ms specifies timeout in milliseconds. */
int nsn_icmp_ping(const char *host, int timeout_ms);

/* Perform a traceroute to the host, up to max_hops hops. Returns 0 on success. */
int nsn_icmp_traceroute(const char *host, int max_hops);

#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_ICMP_H
