/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: networkobject.c
 * Description: Specialised Network (CIDR) object for networking.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *base_addr;
    int prefix_len;
} nsn_network_object;

static void network_dealloc(nsn_object *op) {
    nsn_network_object *no = (nsn_network_object *)op;
    Nsn_XDECREF(no->base_addr);
    NsnMem_Free(no);
}

nsn_type Nsn_NetworkType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "network",
    .tp_basicsize = sizeof(nsn_network_object),
    .tp_dealloc = network_dealloc
};

nsn_object *nsn_network_new(nsn_object *base, int prefix) {
    nsn_network_object *no = (nsn_network_object *)NsnMem_Malloc(sizeof(nsn_network_object));
    if (!no) return NULL;
    
    no->ob_refcnt = 1;
    no->ob_type = &Nsn_NetworkType;
    Nsn_INCREF(base);
    no->base_addr = base;
    no->prefix_len = prefix;
    
    return (nsn_object *)no;
}
