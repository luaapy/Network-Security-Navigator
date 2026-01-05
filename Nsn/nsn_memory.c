/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_memory.c
 * Description: Memory management and allocation system.
 */

#include "nsn.h"
#include <stdlib.h>
#include <string.h>

/*
 * NSN uses a wrapper around malloc/free for tracking and 
 * potential future pool allocation.
 */

void *Nsn_Malloc(size_t size) {
    if (size == 0) return NULL;
    void *ptr = malloc(size);
    if (!ptr) {
        // NsnErr_NoMemory();
        return NULL;
    }
    return ptr;
}

void *Nsn_Realloc(void *ptr, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    void *new_ptr = realloc(ptr, new_size);
    if (!new_ptr) return NULL;
    return new_ptr;
}

void Nsn_Free(void *ptr) {
    if (ptr) free(ptr);
}

void *Nsn_Calloc(size_t nelem, size_t elsize) {
    return calloc(nelem, elsize);
}

char *Nsn_StrDup(const char *str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char *new_str = (char *)Nsn_Malloc(len);
    if (new_str) memcpy(new_str, str, len);
    return new_str;
}
