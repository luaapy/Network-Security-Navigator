/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: codecs.c
 * Description: Handling of string encodings and codecs.
 */

#include "nsn.h"
#include <string.h>

typedef struct {
    const char *name;
    // encoder/decoder function pointers
} nsn_codec;

static nsn_codec _codecs[] = {
    {"utf-8"},
    {"ascii"},
    {"latin-1"},
    {NULL}
};

int NsnCodec_Register(const char *name) {
    /* Add a new codec to the registry */
    return 0;
}

nsn_object *NsnCodec_Encode(const char *str, const char *encoding) {
    if (!encoding) encoding = "utf-8";
    
    // Very simplified: just returns a bytes object
    return nsn_bytes_from_data((const unsigned char *)str, strlen(str));
}

nsn_object *NsnCodec_Decode(const unsigned char *data, size_t len, const char *encoding) {
    if (!encoding) encoding = "utf-8";
    
    // Very simplified: just returns a string object
    return nsn_string_from_cstring((const char *)data);
}
