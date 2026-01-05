/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: importdl.c
 * Description: Loading of dynamic library extensions (.so / .dll).
 */

#include "nsn.h"
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

typedef void (*nsn_init_func)(void);

void *Nsn_LoadDynamicModule(const char *name, const char *path) {
    char func_name[256];
    snprintf(func_name, sizeof(func_name), "_nsn_init_%s", name);

#ifdef _WIN32
    HMODULE handle = LoadLibraryA(path);
    if (!handle) return NULL;
    
    nsn_init_func init = (nsn_init_func)GetProcAddress(handle, func_name);
    if (!init) {
        FreeLibrary(handle);
        return NULL;
    }
#else
    void *handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
    if (!handle) return NULL;
    
    nsn_init_func init = (nsn_init_func)dlsym(handle, func_name);
    if (!init) {
        dlclose(handle);
        return NULL;
    }
#endif

    init();
    return handle;
}
