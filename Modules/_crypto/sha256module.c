/*
 * NSN (Network Security Navigator)
 * SHA256 Hash Module
 */

#include "nsn.h"
#include "security/hash.h"
#include <openssl/sha.h>
#include <string.h>

/* --- Internal Helpers --- */

typedef struct { NSN_OBJECT_HEAD unsigned char *data; size_t length; } nsn_bytes_object;
typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;

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

/* --- SHA256 Implementation --- */

static nsn_object *sha256_hash(nsn_object *self, nsn_object *args) {
    /* Expected args: (data: bytes/string) */
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;

    if (list->size < 1) {
        NsnErr_SetString(NsnExc_TypeError, "hash function requires 1 argument (data)");
        return NULL;
    }

    size_t len;
    const unsigned char *data = as_bytes(list->items[0], &len);

    if (!data) {
        NsnErr_SetString(NsnExc_TypeError, "Argument must be bytes or string");
        return NULL;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(data, len, hash);

    return nsn_bytes_from_data(hash, SHA256_DIGEST_LENGTH);
}

static nsn_object *sha256_hex(nsn_object *self, nsn_object *args) {
    /* Compute SHA256 and return as hex string */
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;

    if (list->size < 1) {
        NsnErr_SetString(NsnExc_TypeError, "hash function requires 1 argument (data)");
        return NULL;
    }

    size_t len;
    const unsigned char *data = as_bytes(list->items[0], &len);
    if (!data) return NULL;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(data, len, hash);

    char hex[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex + (i * 2), "%02x", hash[i]);
    }

    return nsn_string_from_cstring(hex);
}

/* --- Module Registration --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method sha256_methods[] = {
    {"hash", sha256_hash},
    {"hex", sha256_hex},
    {NULL, NULL}
};

void _nsn_init_sha256(void) {
    nsn_object *m = nsn_module_new("sha256");
    // Register methods...
}
