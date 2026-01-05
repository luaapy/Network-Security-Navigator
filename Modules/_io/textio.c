/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: textio.c
 * Description: Text-encoded I/O implementation.
 */

#include "nsn.h"

/*
 * TextIOWrapper provides a text-based interface to a buffered I/O stream.
 * It handles encoding and decoding (e.g., UTF-8).
 */

typedef struct {
    NSN_OBJECT_HEAD
    nsn_object *buffer;
    char *encoding;
} nsn_textio_object;

static void textio_dealloc(nsn_object *op) {
    nsn_textio_object *to = (nsn_textio_object *)op;
    Nsn_XDECREF(to->buffer);
    free(to->encoding);
    NsnMem_Free(to);
}

nsn_type Nsn_TextIOWrapperType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_io.TextIOWrapper",
    .tp_basicsize = sizeof(nsn_textio_object),
    .tp_dealloc = textio_dealloc
};

void _nsn_init_textio(void) {
    /* Text IO types registration */
}
