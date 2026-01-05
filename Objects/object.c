/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Base object implementation
 */

#include "nsn.h"
#include <stdio.h>

void NsnObject_Init(nsn_object *obj, nsn_type *type) {
    obj->ob_refcnt = 1;
    obj->ob_type = type;
}

int NsnObject_Compare(nsn_object *v, nsn_object *w, int op) {
    if (v == w) {
        if (op == NSN_EQ) return 1;
        if (op == NSN_NE) return 0;
    }
    
    // In a real system, we'd check v->ob_type->tp_richcompare
    return -1;
}

nsn_object *NsnObject_GetAttr(nsn_object *v, const char *name) {
    // 1. Check type __dict__
    // 2. Check instance __dict__ (if it exists)
    return NULL;
}

int NsnObject_SetAttr(nsn_object *v, const char *name, nsn_object *value) {
    // 1. Set in instance __dict__
    return -1;
}
