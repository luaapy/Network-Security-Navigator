/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: fileio.c
 * Description: Raw File I/O implementation.
 */

#include "nsn.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* --- File Object Structure --- */

typedef struct {
    NSN_OBJECT_HEAD
    FILE *fp;
    char *mode;
    int closed;
} nsn_file_object;

static void file_dealloc(nsn_object *op) {
    nsn_file_object *fo = (nsn_file_object *)op;
    if (!fo->closed && fo->fp) {
        fclose(fo->fp);
    }
    free(fo->mode);
    NsnMem_Free(fo);
}

nsn_type Nsn_FileType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_io.FileIO",
    .tp_basicsize = sizeof(nsn_file_object),
    .tp_dealloc = file_dealloc
};

/* --- Internal Helpers --- */

typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;
typedef struct { NSN_OBJECT_HEAD unsigned char *data; size_t length; } nsn_bytes_object;
typedef struct { NSN_OBJECT_HEAD long lval; } nsn_int_object;

/* --- Methods --- */

static nsn_object *file_open(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) {
        NsnErr_SetString(NsnExc_TypeError, "open() requires at least a path");
        return NULL;
    }

    if (strcmp(list->items[0]->ob_type->tp_name, "string") != 0) {
        NsnErr_SetString(NsnExc_TypeError, "Path must be a string");
        return NULL;
    }

    const char *path = ((nsn_string_object *)list->items[0])->data;
    const char *mode = "r";
    if (list->size >= 2 && strcmp(list->items[1]->ob_type->tp_name, "string") == 0) {
        mode = ((nsn_string_object *)list->items[1])->data;
    }

    FILE *fp = fopen(path, mode);
    if (!fp) {
        NsnErr_SetString(NsnExc_RuntimeError, strerror(errno));
        return NULL;
    }

    nsn_file_object *fo = (nsn_file_object *)NsnMem_Malloc(sizeof(nsn_file_object));
    fo->ob_refcnt = 1;
    fo->ob_type = &Nsn_FileType;
    fo->fp = fp;
    fo->mode = strdup(mode);
    fo->closed = 0;

    return (nsn_object *)fo;
}

static nsn_object *file_read(nsn_object *self, nsn_object *args) {
    nsn_file_object *fo = (nsn_file_object *)self;
    if (fo->closed) {
        NsnErr_SetString(NsnExc_ValueError, "I/O operation on closed file");
        return NULL;
    }

    long size = -1;
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size >= 1 && strcmp(list->items[0]->ob_type->tp_name, "int") == 0) {
        size = ((nsn_int_object *)list->items[0])->lval;
    }

    if (size < 0) {
        // Read until EOF
        fseek(fo->fp, 0, SEEK_END);
        size = ftell(fo->fp);
        fseek(fo->fp, 0, SEEK_SET);
    }

    unsigned char *buffer = malloc(size);
    size_t n = fread(buffer, 1, size, fo->fp);
    
    nsn_object *res = nsn_bytes_from_data(buffer, n);
    free(buffer);
    return res;
}

static nsn_object *file_write(nsn_object *self, nsn_object *args) {
    nsn_file_object *fo = (nsn_file_object *)self;
    if (fo->closed) {
        NsnErr_SetString(NsnExc_ValueError, "I/O operation on closed file");
        return NULL;
    }

    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return nsn_int_from_long(0);

    const unsigned char *data;
    size_t len;
    
    if (strcmp(list->items[0]->ob_type->tp_name, "bytes") == 0) {
        nsn_bytes_object *bo = (nsn_bytes_object *)list->items[0];
        data = bo->data;
        len = bo->length;
    } else if (strcmp(list->items[0]->ob_type->tp_name, "string") == 0) {
        nsn_string_object *so = (nsn_string_object *)list->items[0];
        data = (const unsigned char *)so->data;
        len = strlen(so->data);
    } else {
        NsnErr_SetString(NsnExc_TypeError, "write() requires bytes or string");
        return NULL;
    }

    size_t n = fwrite(data, 1, len, fo->fp);
    return nsn_int_from_long((long)n);
}

static nsn_object *file_close(nsn_object *self, nsn_object *args) {
    nsn_file_object *fo = (nsn_file_object *)self;
    if (!fo->closed) {
        fclose(fo->fp);
        fo->closed = 1;
    }
    Nsn_INCREF(Nsn_None);
    return Nsn_None;
}

/* --- Module Setup --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method file_methods[] = {
    {"open", file_open},
    {"read", file_read},
    {"write", file_write},
    {"close", file_close},
    {NULL, NULL}
};

void _nsn_init_fileio(void) {
    nsn_object *m = nsn_module_new("_io");
    // Register methods...
}
