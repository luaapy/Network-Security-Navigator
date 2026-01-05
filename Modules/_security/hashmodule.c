/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: hashmodule.c
 * Description: Unified hashing interface using OpenSSL.
 */

#include "nsn.h"
#include <openssl/evp.h>
#include <string.h>

static nsn_object *do_hash_evp(const EVP_MD *md, const unsigned char *data, size_t len) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, data, len);
    EVP_DigestFinal_ex(ctx, hash, &hash_len);
    EVP_MD_CTX_free(ctx);

    char hex[EVP_MAX_MD_SIZE * 2 + 1];
    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hex + (i * 2), "%02x", hash[i]);
    }

    return nsn_string_from_cstring(hex);
}

nsn_object *nsn_hash_sha256(const unsigned char *data, size_t len) {
    return do_hash_evp(EVP_sha256(), data, len);
}

nsn_object *nsn_hash_md5(const unsigned char *data, size_t len) {
    return do_hash_evp(EVP_md5(), data, len);
}

nsn_object *nsn_hash_sha1(const unsigned char *data, size_t len) {
    return do_hash_evp(EVP_sha1(), data, len);
}

void _nsn_init_hash(void) {
    nsn_object *m = nsn_module_new("hash");
}
