/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Import system implementation
 */

#include "nsn.h"
#include <stdio.h>
#include <string.h>

static nsn_object *loaded_modules = NULL;

void NsnImport_Init(void) {
    loaded_modules = nsn_dict_new();
}

void NsnImport_Cleanup(void) {
    Nsn_XDECREF(loaded_modules);
    loaded_modules = NULL;
}

nsn_object *Nsn_ImportModule(const char *name) {
    if (!loaded_modules) NsnImport_Init();

    nsn_object *name_obj = nsn_string_from_cstring(name);
    nsn_object *mod = nsn_dict_get_item(loaded_modules, name_obj);
    if (mod) {
        Nsn_DECREF(name_obj);
        return mod;
    }

    /* 
     * Try searching for the module.
     * In this phase, we support:
     * 1. Internal frozen modules
     * 2. Filesystem search within NSNPATH
     */
    
    // Check frozen first (bootstrapping)
    mod = NsnFrozen_LoadModule(name);
    if (mod) {
        nsn_dict_set_item(loaded_modules, name_obj, mod);
        Nsn_DECREF(name_obj);
        return mod;
    }

    // Filesystem search
    const char *nsn_path = Nsn_GetPath();
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "%s/%s.nsn", nsn_path, name);
    
    FILE *f = fopen(full_path, "r");
    if (f) {
        fclose(f);
        mod = Nsn_RunFile(full_path);
        if (mod) {
            nsn_dict_set_item(loaded_modules, name_obj, mod);
        }
    }

    Nsn_DECREF(name_obj);
    return mod;
}
