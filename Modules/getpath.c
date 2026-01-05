/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: getpath.c
 * Description: Logic for calculating the search path for modules.
 */

#include "nsn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#define PATH_SEP ";"
#else
#include <unistd.h>
#define PATH_SEP ":"
#endif

static char *nsn_path = NULL;

const char *Nsn_GetPath(void) {
    if (nsn_path) return nsn_path;

    const char *env_path = getenv("NSNPATH");
    if (env_path) {
        nsn_path = strdup(env_path);
        return nsn_path;
    }

    // Default search paths
#ifdef WIN32
    nsn_path = strdup(".;.\\Lib;.\\Modules");
#else
    nsn_path = strdup(".:./Lib:/usr/local/lib/nsn:/usr/lib/nsn");
#endif

    return nsn_path;
}

void Nsn_SetPath(const char *path) {
    if (nsn_path) free(nsn_path);
    nsn_path = strdup(path);
}

void _nsn_init_getpath(void) {
    // Path calculation logic
}
