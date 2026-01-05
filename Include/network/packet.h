/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Packet handling
 */

#ifndef NSN_NETWORK_PACKET_H
#define NSN_NETWORK_PACKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* Packet object representing raw data */
typedef struct {
    nsn_object base;
    unsigned char *raw;
    size_t size;
} nsn_packet_object;

/* Create a new packet object from raw data */
nsn_object *nsn_packet_new(const unsigned char *data, size_t len);

/* Retrieve a field from the packet (e.g., src IP, dst IP, protocol). */
int nsn_packet_get_field(nsn_object *pkt, const char *field, void *out);

#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_PACKET_H
