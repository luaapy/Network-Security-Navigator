/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: traceback.c
 * Description: Traceback object and error reporting.
 */

#include "nsn.h"
#include <stdio.h>

typedef struct {
    NSN_OBJECT_HEAD
    nsn_frame *frame;
    int line;
    struct _nsn_traceback *next;
} nsn_traceback_object;

static void traceback_dealloc(nsn_object *op) {
    nsn_traceback_object *tb = (nsn_traceback_object *)op;
    // Nsn_XDECREF(tb->frame);
    // Nsn_XDECREF(tb->next);
    NsnMem_Free(tb);
}

nsn_type Nsn_TracebackType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "traceback",
    .tp_basicsize = sizeof(nsn_traceback_object),
    .tp_dealloc = traceback_dealloc
};

void NsnTraceback_Print(nsn_object *tb_obj) {
    nsn_traceback_object *tb = (nsn_traceback_object *)tb_obj;
    printf("Traceback (most recent call last):\n");
    while (tb) {
        // printf("  File \"%s\", line %d\n", ...);
        tb = (nsn_traceback_object *)tb->next;
    }
}