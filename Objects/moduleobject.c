/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: moduleobject.c
 * Description: Implementation of the NSN module object.
 */

#include "nsn.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *md_dict;
    nsn_object *md_name;
} nsn_module_object;

static void module_dealloc(nsn_object *op) {
    nsn_module_object *m = (nsn_module_object *)op;
    Nsn_XDECREF(m->md_dict);
    Nsn_XDECREF(m->md_name);
    NsnMem_Free(m);
}

nsn_type Nsn_ModuleType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "module",
    .tp_basicsize = sizeof(nsn_module_object),
    .tp_dealloc = module_dealloc
};

nsn_object *nsn_module_new(const char *name) {
    nsn_module_object *m = (nsn_module_object *)NsnMem_Malloc(sizeof(nsn_module_object));
    if (!m) return NULL;
    
    m->ob_refcnt = 1;
    m->ob_type = &Nsn_ModuleType;
    m->md_name = nsn_string_from_cstring(name);
    m->md_dict = nsn_dict_new();
    
    // Set __name__ in module dict
    nsn_dict_set_item(m->md_dict, nsn_string_from_cstring("__name__"), m->md_name);
    
    return (nsn_object *)m;
}

nsn_object *nsn_module_get_dict(nsn_object *m) {
    if (m->ob_type != &Nsn_ModuleType) return NULL;
    return ((nsn_module_object *)m)->md_dict;
}

void nsn_module_add_object(nsn_object *m, const char *name, nsn_object *obj) {
    nsn_object *dict = nsn_module_get_dict(m);
    nsn_object *key = nsn_string_from_cstring(name);
    nsn_dict_set_item(dict, key, obj);
    Nsn_DECREF(key);
}
