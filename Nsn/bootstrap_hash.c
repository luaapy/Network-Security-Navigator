/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: bootstrap_hash.c
 * Description: Simple hashing for internal bootstrapping (e.g., hash tables).
 */

#include "nsn.h"
#include <stdint.h>
#include <stddef.h>

/* FNV-1a Hash Implementation */
uint64_t Nsn_HashString(const char *str) {
    uint64_t hash = 0xcbf29ce484222325ULL;
    const uint64_t prime = 0x100000001b3ULL;

    while (*str) {
        hash ^= (uint64_t)(unsigned char)(*str++);
        hash *= prime;
    }
    return hash;
}

uint64_t Nsn_HashBytes(const unsigned char *data, size_t len) {
    uint64_t hash = 0xcbf29ce484222325ULL;
    const uint64_t prime = 0x100000001b3ULL;

    for (size_t i = 0; i < len; i++) {
        hash ^= (uint64_t)data[i];
        hash *= prime;
    }
    return hash;
}
