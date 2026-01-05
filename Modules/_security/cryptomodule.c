/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: cryptomodule.c
 * Description: High-level cryptography (RSA, Randomness) implementation.
 */

#include "nsn.h"
#include "security/crypto.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <string.h>

/* --- RSA Object Structure --- */

typedef struct {
    NSN_OBJECT_HEAD
    RSA *rsa;
    int is_private;
} nsn_rsa_object;

static void rsa_dealloc(nsn_object *op) {
    nsn_rsa_object *ro = (nsn_rsa_object *)op;
    if (ro->rsa) RSA_free(ro->rsa);
    NsnMem_Free(ro);
}

nsn_type Nsn_RSAType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_security.RSA",
    .tp_basicsize = sizeof(nsn_rsa_object),
    .tp_dealloc = rsa_dealloc
};

/* --- Internal Helpers --- */

typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
typedef struct { NSN_OBJECT_HEAD unsigned char *data; size_t length; } nsn_bytes_object;
typedef struct { NSN_OBJECT_HEAD long lval; } nsn_int_object;

/* --- RSA Methods --- */

static nsn_object *crypto_generate_rsa(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    int bits = 2048;
    if (list->size >= 1 && strcmp(list->items[0]->ob_type->tp_name, "int") == 0) {
        bits = (int)((nsn_int_object *)list->items[0])->lval;
    }

    BIGNUM *bn = BN_new();
    BN_set_word(bn, RSA_F4);
    RSA *rsa = RSA_new();
    
    if (RSA_generate_key_ex(rsa, bits, bn, NULL) != 1) {
        BN_free(bn);
        RSA_free(rsa);
        NsnErr_SetString(NsnExc_SecurityError, "RSA key generation failed");
        return NULL;
    }
    BN_free(bn);

    nsn_rsa_object *ro = (nsn_rsa_object *)NsnMem_Malloc(sizeof(nsn_rsa_object));
    ro->ob_refcnt = 1;
    ro->ob_type = &Nsn_RSAType;
    ro->rsa = rsa;
    ro->is_private = 1;

    return (nsn_object *)ro;
}

static nsn_object *crypto_random_bytes(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;

    long len = ((nsn_int_object *)list->items[0])->lval;
    unsigned char *buf = malloc(len);
    
    if (RAND_bytes(buf, (int)len) != 1) {
        free(buf);
        NsnErr_SetString(NsnExc_SecurityError, "PRNG failed");
        return NULL;
    }

    nsn_object *res = nsn_bytes_from_data(buf, len);
    free(buf);
    return res;
}

/* --- RSA Object Methods --- */

static nsn_object *rsa_encrypt(nsn_object *self, nsn_object *args) {
    nsn_rsa_object *ro = (nsn_rsa_object *)self;
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;

    nsn_bytes_object *bo = (nsn_bytes_object *)list->items[0];
    unsigned char *out = malloc(RSA_size(ro->rsa));
    
    int n = RSA_public_encrypt((int)bo->length, bo->data, out, ro->rsa, RSA_PKCS1_OAEP_PADDING);
    if (n < 0) {
        free(out);
        NsnErr_SetString(NsnExc_SecurityError, "RSA encryption failed");
        return NULL;
    }

    nsn_object *res = nsn_bytes_from_data(out, n);
    free(out);
    return res;
}

/* --- Module Setup --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method crypto_methods[] = {
    {"generate_rsa", crypto_generate_rsa},
    {"random_bytes", crypto_random_bytes},
    {NULL, NULL}
};

void _nsn_init_crypto(void) {
    nsn_object *m = nsn_module_new("_security");
    // Register methods...
}
