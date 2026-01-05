/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _json.c
 * Description: JSON serialization and deserialization.
 */

#include "nsn.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* --- Internal Helpers --- */

typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;
typedef struct { NSN_OBJECT_HEAD long lval; } nsn_int_object;
typedef struct { NSN_OBJECT_HEAD double dval; } nsn_float_object;
typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_object;
typedef struct { NSN_OBJECT_HEAD nsn_object *dict; } nsn_dict_object;

/* --- Serializer --- */

static void json_encode_recursive(nsn_object *obj, char **buf, size_t *cap, size_t *len) {
    if (obj == Nsn_None) {
        snprintf(*buf + *len, *cap - *len, "null");
        *len += 4;
    } else if (obj == Nsn_True) {
        snprintf(*buf + *len, *cap - *len, "true");
        *len += 4;
    } else if (obj == Nsn_False) {
        snprintf(*buf + *len, *cap - *len, "false");
        *len += 5;
    } else if (strcmp(obj->ob_type->tp_name, "int") == 0) {
        int n = snprintf(*buf + *len, *cap - *len, "%ld", ((nsn_int_object *)obj)->lval);
        *len += n;
    } else if (strcmp(obj->ob_type->tp_name, "float") == 0) {
        int n = snprintf(*buf + *len, *cap - *len, "%g", ((nsn_float_object *)obj)->dval);
        *len += n;
    } else if (strcmp(obj->ob_type->tp_name, "string") == 0) {
        int n = snprintf(*buf + *len, *cap - *len, "\"%s\"", ((nsn_string_object *)obj)->data);
        *len += n;
    } else if (strcmp(obj->ob_type->tp_name, "list") == 0) {
        nsn_list_object *lo = (nsn_list_object *)obj;
        (*buf)[(*len)++] = '[';
        for (int i = 0; i < lo->size; i++) {
            json_encode_recursive(lo->items[i], buf, cap, len);
            if (i < lo->size - 1) (*buf)[(*len)++] = ',';
        }
        (*buf)[(*len)++] = ']';
    } 
    // ... Dict handle would go here ...
}

static nsn_object *json_dumps(nsn_object *self, nsn_object *args) {
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;

    size_t cap = 1024;
    size_t len = 0;
    char *buf = malloc(cap);
    
    json_encode_recursive(list->items[0], &buf, &cap, &len);
    buf[len] = '\0';

    nsn_object *res = nsn_string_from_cstring(buf);
    free(buf);
    return res;
}

/* --- Parser (Skeleton) --- */

static nsn_object *json_loads(nsn_object *self, nsn_object *args) {
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;

    const char *json_str = ((nsn_string_object *)list->items[0])->data;
    
    // Very basic primitive parser stub
    if (strcmp(json_str, "null") == 0) { Nsn_INCREF(Nsn_None); return Nsn_None; }
    if (strcmp(json_str, "true") == 0) { Nsn_INCREF(Nsn_True); return Nsn_True; }
    if (strcmp(json_str, "false") == 0) { Nsn_INCREF(Nsn_False); return Nsn_False; }
    
    return nsn_int_from_long(atol(json_str)); // Dummy
}

/* --- Module Setup --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method json_methods[] = {
    {"dumps", json_dumps},
    {"loads", json_loads},
    {NULL, NULL}
};

void _nsn_init_json(void) {
    nsn_object *m = nsn_module_new("json");
    // Register methods...
}
