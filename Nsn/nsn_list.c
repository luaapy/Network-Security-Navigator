/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_list.c
 * Description: Implementation of the 'list' (dynamic array) object.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object **items;
    size_t size;
    size_t capacity;
} nsn_list_object;

static void list_dealloc(nsn_object *op) {
    nsn_list_object *lo = (nsn_list_object *)op;
    for (size_t i = 0; i < lo->size; i++) {
        Nsn_XDECREF(lo->items[i]);
    }
    if (lo->items) free(lo->items);
    NsnMem_Free(lo);
}

nsn_type Nsn_ListType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "list",
    .tp_basicsize = sizeof(nsn_list_object),
    .tp_dealloc = list_dealloc
};

nsn_object *nsn_list_new(void) {
    nsn_list_object *lo = (nsn_list_object *)NsnMem_Malloc(sizeof(nsn_list_object));
    if (!lo) return NULL;
    lo->ob_refcnt = 1;
    lo->ob_type = &Nsn_ListType;
    lo->items = NULL;
    lo->size = 0;
    lo->capacity = 0;
    return (nsn_object *)lo;
}

int nsn_list_append(nsn_object *self, nsn_object *item) {
    nsn_list_object *lo = (nsn_list_object *)self;
    if (lo->size >= lo->capacity) {
        size_t new_cap = lo->capacity ? lo->capacity * 2 : 4;
        nsn_object **new_items = realloc(lo->items, new_cap * sizeof(nsn_object *));
        if (!new_items) return -1;
        lo->items = new_items;
        lo->capacity = new_cap;
    }
    Nsn_XINCREF(item);
    lo->items[lo->size++] = item;
    return 0;
}

size_t nsn_list_size(nsn_object *self) {
    return ((nsn_list_object *)self)->size;
}

nsn_object *nsn_list_get_item(nsn_object *self, size_t index) {
    nsn_list_object *lo = (nsn_list_object *)self;
    if (index >= lo->size) return NULL;
    return lo->items[index];
}
