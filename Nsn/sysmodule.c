/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: sysmodule.c
 * Description: System-specific parameters and functions.
 */

#include "nsn.h"
#include <stdio.h>
#include <string.h>

static nsn_object *sys_get_platform(nsn_object *self, nsn_object *args) {
    return nsn_string_from_cstring(Nsn_GetPlatform());
}

static nsn_object *sys_get_path(nsn_object *self, nsn_object *args) {
    return nsn_string_from_cstring(Nsn_GetPath());
}

static nsn_object *sys_set_path(nsn_object *self, nsn_object *args) {
    // Expect one string argument
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;
    
    typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;
    Nsn_SetPath(((nsn_string_object*)list->items[0])->data);
    
    Nsn_INCREF(Nsn_None);
    return Nsn_None;
}

static nsn_method sys_methods[] = {
    {"get_platform", sys_get_platform},
    {"get_path", sys_get_path},
    {"set_path", sys_set_path},
    {NULL, NULL}
};

void _nsn_init_sys(void) {
    nsn_object *m = nsn_module_new("sys");
    // Register attributes like argv, version, etc.
}
