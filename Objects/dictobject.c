/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: dictobject.c
 * Description: Robust dictionary (hash map) implementation.
 */

#include "nsn.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    nsn_object *key;
    nsn_object *value;
    long hash;
} nsn_dict_entry;

typedef struct {
    NSN_OBJECT_HEAD
    nsn_dict_entry *ma_table;
    size_t ma_used;
    size_t ma_mask;
} nsn_dict_object;

static void dict_dealloc(nsn_object *op) {
    nsn_dict_object *mp = (nsn_dict_object *)op;
    for (size_t i = 0; i <= mp->ma_mask; i++) {
        Nsn_XDECREF(mp->ma_table[i].key);
        Nsn_XDECREF(mp->ma_table[i].value);
    }
    if (mp->ma_table) free(mp->ma_table);
    NsnMem_Free(mp);
}

nsn_type Nsn_DictType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "dict",
    .tp_basicsize = sizeof(nsn_dict_object),
    .tp_dealloc = dict_dealloc
};

nsn_object *nsn_dict_new(void) {
    nsn_dict_object *mp = (nsn_dict_object *)NsnMem_Malloc(sizeof(nsn_dict_object));
    if (!mp) return NULL;
    
    mp->ob_refcnt = 1;
    mp->ob_type = &Nsn_DictType;
    mp->ma_used = 0;
    mp->ma_mask = 7;
    mp->ma_table = (nsn_dict_entry *)calloc(8, sizeof(nsn_dict_entry));
    
    return (nsn_object *)mp;
}

int nsn_dict_set_item(nsn_object *op, nsn_object *key, nsn_object *value) {
    nsn_dict_object *mp = (nsn_dict_object *)op;
    long hash = Nsn_Hash(key);
    size_t i = (size_t)hash & mp->ma_mask;
    
    /* Simplified collision handling: linear probing */
    while (mp->ma_table[i].key != NULL && mp->ma_table[i].key != key) {
        i = (i + 1) & mp->ma_mask;
    }
    
    if (mp->ma_table[i].key == NULL) {
        mp->ma_used++;
    }
    
    Nsn_XINCREF(key);
    Nsn_XINCREF(value);
    Nsn_XDECREF(mp->ma_table[i].key);
    Nsn_XDECREF(mp->ma_table[i].value);
    
    mp->ma_table[i].key = key;
    mp->ma_table[i].value = value;
    mp->ma_table[i].hash = hash;
    
    return 0;
}

nsn_object *nsn_dict_get_item(nsn_object *op, nsn_object *key) {
    nsn_dict_object *mp = (nsn_dict_object *)op;
    long hash = Nsn_Hash(key);
    size_t i = (size_t)hash & mp->ma_mask;
    
    while (mp->ma_table[i].key != NULL) {
        if (mp->ma_table[i].key == key) return mp->ma_table[i].value;
        i = (i + 1) & mp->ma_mask;
    }
    
    return NULL;
}
