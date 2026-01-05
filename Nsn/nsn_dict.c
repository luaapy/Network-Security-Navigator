/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_dict.c
 * Description: Implementation of the 'dict' (hash map) object.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    nsn_object *key;
    nsn_object *value;
} nsn_dict_entry;

typedef struct {
    NSN_OBJECT_HEAD
    nsn_dict_entry *entries;
    size_t size;
    size_t capacity;
} nsn_dict_object;

static void dict_dealloc(nsn_object *op) {
    nsn_dict_object *do_obj = (nsn_dict_object *)op;
    for (size_t i = 0; i < do_obj->capacity; i++) {
        Nsn_XDECREF(do_obj->entries[i].key);
        Nsn_XDECREF(do_obj->entries[i].value);
    }
    if (do_obj->entries) free(do_obj->entries);
    NsnMem_Free(do_obj);
}

nsn_type Nsn_DictType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "dict",
    .tp_basicsize = sizeof(nsn_dict_object),
    .tp_dealloc = dict_dealloc
};

nsn_object *nsn_dict_new(void) {
    nsn_dict_object *do_obj = (nsn_dict_object *)NsnMem_Malloc(sizeof(nsn_dict_object));
    if (!do_obj) return NULL;
    do_obj->ob_refcnt = 1;
    do_obj->ob_type = &Nsn_DictType;
    do_obj->capacity = 8; // Small default
    do_obj->size = 0;
    do_obj->entries = calloc(do_obj->capacity, sizeof(nsn_dict_entry));
    return (nsn_object *)do_obj;
}

int nsn_dict_set_item(nsn_object *self, nsn_object *key, nsn_object *value) {
    nsn_dict_object *do_obj = (nsn_dict_object *)self;
    // Simplified: Linear search for demo
    for (size_t i = 0; i < do_obj->capacity; i++) {
        if (do_obj->entries[i].key == key) {
            Nsn_XDECREF(do_obj->entries[i].value);
            Nsn_XINCREF(value);
            do_obj->entries[i].value = value;
            return 0;
        }
        if (do_obj->entries[i].key == NULL) {
            Nsn_XINCREF(key);
            Nsn_XINCREF(value);
            do_obj->entries[i].key = key;
            do_obj->entries[i].value = value;
            do_obj->size++;
            return 0;
        }
    }
    return -1; // Full
}

nsn_object *nsn_dict_get_item(nsn_object *self, nsn_object *key) {
    nsn_dict_object *do_obj = (nsn_dict_object *)self;
    for (size_t i = 0; i < do_obj->capacity; i++) {
        if (do_obj->entries[i].key == key) {
            return do_obj->entries[i].value;
        }
    }
    return NULL;
}
