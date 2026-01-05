/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _nsnmodule.c
 * Description: The main "nsn" module providing interpreter info and system hooks.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>

static nsn_object *nsn_version(nsn_object *self, nsn_object *args) {
    return nsn_string_from_cstring(NSN_VERSION_STRING);
}

static nsn_object *nsn_get_config(nsn_object *self, nsn_object *args) {
    // Return a dict containing current configuration
    nsn_object *dict = nsn_dict_new();
    // Nsn_GetConfig() ... add items
    return dict;
}

static nsn_object *nsn_exit(nsn_object *self, nsn_object *args) {
    int code = 0;
    // Parse args for exit code
    exit(code);
    return Nsn_None; // Never reached
}

static nsn_method nsn_methods[] = {
    {"version", nsn_version},
    {"get_config", nsn_get_config},
    {"exit", nsn_exit},
    {NULL, NULL}
};

void _nsn_init_nsnmodule(void) {
    nsn_object *m = nsn_module_new("nsn");
    // Register methods...
    nsn_module_add_object(m, "version_info", nsn_version(NULL, NULL));
}
