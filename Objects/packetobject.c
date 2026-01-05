/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: packetobject.c
 * Description: Raw network packet object implementation.
 */

#include "nsn.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    NSN_OBJECT_HEAD
    unsigned char *raw_data;
    size_t length;
} nsn_packet_object;

static void packet_dealloc(nsn_object *op) {
    nsn_packet_object *po = (nsn_packet_object *)op;
    if (po->raw_data) free(po->raw_data);
    NsnMem_Free(po);
}

nsn_type Nsn_PacketType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "Packet",
    .tp_basicsize = sizeof(nsn_packet_object),
    .tp_dealloc = packet_dealloc
};

nsn_object *nsn_packet_new(const unsigned char *data, size_t len) {
    nsn_packet_object *po = (nsn_packet_object *)NsnMem_Malloc(sizeof(nsn_packet_object));
    if (!po) return NULL;
    
    po->ob_refcnt = 1;
    po->ob_type = &Nsn_PacketType;
    po->length = len;
    po->raw_data = (unsigned char *)malloc(len);
    if (po->raw_data) memcpy(po->raw_data, data, len);
    
    return (nsn_object *)po;
}
