/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * DNS operations
 */

#ifndef NSN_NETWORK_DNS_H
#define NSN_NETWORK_DNS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* Resolve a hostname to an IP address string. Returns an NSN string object or NULL on error */
nsn_object *nsn_dns_resolve(const char *hostname);

/* Perform a reverse DNS lookup on an IP address string. Returns an NSN string object */
nsn_object *nsn_dns_reverse(const char *ip);

#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_DNS_H
