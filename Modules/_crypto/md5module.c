/*
 * NSN (Network Security Navigator)
 * MD5 Hash Module
 */

#include "nsn.h"
#include "security/hash.h"
#include <openssl/md5.h>
#include <string.h>
#include <stdio.h>

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

/* --- MD5 Implementation --- */

static nsn_object *md5_hash(nsn_object *self, nsn_object *args) {
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;

    if (list->size < 1) {
        NsnErr_SetString(NsnExc_TypeError, "md5 function requires 1 argument (data)");
        return NULL;
    }

    size_t len;
    const unsigned char *data = as_bytes(list->items[0], &len);
    if (!data) {
        NsnErr_SetString(NsnExc_TypeError, "Argument must be bytes or string");
        return NULL;
    }

    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5(data, len, hash);

    return nsn_bytes_from_data(hash, MD5_DIGEST_LENGTH);
}

static nsn_object *md5_hex(nsn_object *self, nsn_object *args) {
    typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
    nsn_list_view *list = (nsn_list_view *)args;

    if (list->size < 1) {
        NsnErr_SetString(NsnExc_TypeError, "md5 function requires 1 argument (data)");
        return NULL;
    }

    size_t len;
    const unsigned char *data = as_bytes(list->items[0], &len);
    if (!data) return NULL;

    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5(data, len, hash);

    char hex[MD5_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hex + (i * 2), "%02x", hash[i]);
    }

    return nsn_string_from_cstring(hex);
}

/* --- Module Registration --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method md5_methods[] = {
    {"hash", md5_hash},
    {"hex", md5_hex},
    {NULL, NULL}
};

void _nsn_init_md5(void) {
    nsn_object *m = nsn_module_new("md5");
    // Register methods...
}
