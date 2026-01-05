/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Hash functions core interface
 */

#ifndef NSN_SECURITY_HASH_H
#define NSN_SECURITY_HASH_H

#include "core/object.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compute SHA256 hash of data.
 * Returns 32 bytes of hash.
 */
int nsn_hash_sha256(const unsigned char *data, size_t len, unsigned char *out);

/**
 * Compute MD5 hash of data.
 * Returns 16 bytes of hash.
 */
int nsn_hash_md5(const unsigned char *data, size_t len, unsigned char *out);

/**
 * Compute SHA512 hash of data.
 * Returns 64 bytes of hash.
 */
int nsn_hash_sha512(const unsigned char *data, size_t len, unsigned char *out);

#ifdef __cplusplus
}
#endif

#endif // NSN_SECURITY_HASH_H
