/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: ipaddrobject.c
 * Description: Specialised IP address object for networking.
 */

#include "nsn.h"
#include <string.h>

#ifdef WIN32
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

typedef struct {
    NSN_OBJECT_HEAD
    char addr[64];
    int version;
} nsn_ipaddr_object;

static void ipaddr_dealloc(nsn_object *op) {
    NsnMem_Free(op);
}

nsn_type Nsn_IPAddrType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "ip_address",
    .tp_basicsize = sizeof(nsn_ipaddr_object),
    .tp_dealloc = ipaddr_dealloc
};

nsn_object *nsn_ipaddr_from_string(const char *str) {
    nsn_ipaddr_object *io = (nsn_ipaddr_object *)NsnMem_Malloc(sizeof(nsn_ipaddr_object));
    if (!io) return NULL;
    
    io->ob_refcnt = 1;
    io->ob_type = &Nsn_IPAddrType;
    strncpy(io->addr, str, 63);
    io->addr[63] = '\0';
    io->version = (strchr(str, ':') != NULL) ? 6 : 4;
    
    return (nsn_object *)io;
}
