/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: portobject.c
 * Description: Port object for network scanning.
 */

#include "nsn.h"

typedef struct {
    NSN_OBJECT_HEAD
    int number;
    char protocol[8];
} nsn_port_object;

static void port_dealloc(nsn_object *op) {
    NsnMem_Free(op);
}

nsn_type Nsn_PortType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "port",
    .tp_basicsize = sizeof(nsn_port_object),
    .tp_dealloc = port_dealloc
};

nsn_object *nsn_port_new(int number, const char *proto) {
    nsn_port_object *po = (nsn_port_object *)NsnMem_Malloc(sizeof(nsn_port_object));
    if (!po) return NULL;
    
    po->ob_refcnt = 1;
    po->ob_type = &Nsn_PortType;
    po->number = number;
    strncpy(po->protocol, proto ? proto : "tcp", 7);
    po->protocol[7] = '\0';
    
    return (nsn_object *)po;
}
