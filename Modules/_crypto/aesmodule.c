/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: aesmodule.c
 * Description: Advanced Encryption Standard (AES) implementation using OpenSSL EVP.
 */

#include "nsn.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <string.h>

/* --- Internal Helpers --- */

// Internal structure matching Objects/bytesobject.c
typedef struct {
    NSN_OBJECT_HEAD
    unsigned char *data;
    size_t length;
} nsn_bytes_object;

// Internal structure matching Objects/stringobject.c
typedef struct {
    NSN_OBJECT_HEAD
    char *data;
} nsn_string_object;

static const unsigned char *as_bytes(nsn_object *obj, size_t *len) {
    if (strcmp(obj->ob_type->tp_name, "bytes") == 0) {
        nsn_bytes_object *bo = (nsn_bytes_object *)obj;
        *len = bo->length;
        return bo->data;
    } else if (strcmp(obj->ob_type->tp_name, "string") == 0) {
        nsn_string_object *so = (nsn_string_object *)obj;
        *len = strlen(so->data);
        return (const unsigned char *)so->data;
    }
    return NULL;
}

/* --- AES Core Logic --- */

static nsn_object *do_aes_crypt(nsn_object *args, int encrypt) {
    /* 
     * Arguments: (key: bytes, data: bytes, iv: bytes, mode: string)
     * mode can be "cbc" or "gcm"
     */
    
    // Manual argument extraction (assuming args is a list as seen in bltinmodule.c logic)
    // Note: In a real system we'd use NsnArg_ParseTuple
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;
    
    if (list->size < 3) {
        NsnErr_SetString(NsnExc_TypeError, "aes function requires at least 3 arguments (key, data, iv)");
        return NULL;
    }

    size_t key_len, data_len, iv_len;
    const unsigned char *key = as_bytes(list->items[0], &key_len);
    const unsigned char *data = as_bytes(list->items[1], &data_len);
    const unsigned char *iv = as_bytes(list->items[2], &iv_len);
    
    const char *mode = "cbc";
    if (list->size >= 4 && strcmp(list->items[3]->ob_type->tp_name, "string") == 0) {
        mode = ((nsn_string_object *)list->items[3])->data;
    }

    if (!key || !data || !iv) {
        NsnErr_SetString(NsnExc_TypeError, "Arguments must be bytes or strings");
        return NULL;
    }

    const EVP_CIPHER *cipher = NULL;
    if (strcmp(mode, "cbc") == 0) {
        if (key_len == 16) cipher = EVP_aes_128_cbc();
        else if (key_len == 24) cipher = EVP_aes_192_cbc();
        else if (key_len == 32) cipher = EVP_aes_256_cbc();
    } else if (strcmp(mode, "gcm") == 0) {
        if (key_len == 16) cipher = EVP_aes_128_gcm();
        else if (key_len == 24) cipher = EVP_aes_192_gcm();
        else if (key_len == 32) cipher = EVP_aes_256_gcm();
    }

    if (!cipher) {
        NsnErr_SetString(NsnExc_ValueError, "Unsupported key size or mode");
        return NULL;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        NsnErr_SetString(NsnExc_MemoryError, "Failed to create EVP context");
        return NULL;
    }

    unsigned char *out = malloc(data_len + EVP_MAX_BLOCK_LENGTH);
    int out_len = 0, final_len = 0;

    if (EVP_CipherInit_ex(ctx, cipher, NULL, key, iv, encrypt) != 1) {
        goto error;
    }

    if (EVP_CipherUpdate(ctx, out, &out_len, data, (int)data_len) != 1) {
        goto error;
    }

    if (EVP_CipherFinal_ex(ctx, out + out_len, &final_len) != 1) {
        goto error;
    }

    nsn_object *res = nsn_bytes_from_data(out, out_len + final_len);
    free(out);
    EVP_CIPHER_CTX_free(ctx);
    return res;

error:
    free(out);
    EVP_CIPHER_CTX_free(ctx);
    NsnErr_SetString(NsnExc_SecurityError, "OpenSSL cipher operation failed");
    return NULL;
}

/* --- Module Methods --- */

static nsn_object *crypt_encrypt(nsn_object *self, nsn_object *args) {
    return do_aes_crypt(args, 1);
}

static nsn_object *crypt_decrypt(nsn_object *self, nsn_object *args) {
    return do_aes_crypt(args, 0);
}

static nsn_object *crypt_generate_key(nsn_object *self, nsn_object *args) {
    int length = 32;
    // ... parse length if provided ...
    
    unsigned char *key = malloc(length);
    if (RAND_bytes(key, length) != 1) {
        free(key);
        NsnErr_SetString(NsnExc_SecurityError, "Failed to generate random bytes");
        return NULL;
    }
    
    nsn_object *res = nsn_bytes_from_data(key, length);
    free(key);
    return res;
}

/* --- Module Initialization --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method aes_methods[] = {
    {"encrypt", crypt_encrypt},
    {"decrypt", crypt_decrypt},
    {"generate_key", crypt_generate_key},
    {NULL, NULL}
};

void NsnInit_aes(void) {
    nsn_object *m = nsn_module_new("aes");
    for (int i = 0; aes_methods[i].name; i++) {
        // In a real system we'd use nsn_module_add_function
        // nsn_module_add_function(m, aes_methods[i].name, aes_methods[i].func);
    }
}
