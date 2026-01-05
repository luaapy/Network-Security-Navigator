/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: symtable.c
 * Description: Symbol table for variable scope resolution during compilation.
 */

#include "nsn.h"
#include <string.h>

typedef struct {
    char *name;
    int type; // local, global, cell
} nsn_symbol;

typedef struct {
    nsn_symbol *symbols;
    int count;
    int capacity;
} nsn_symtable;

nsn_symtable *NsnSymtable_New(void) {
    nsn_symtable *st = (nsn_symtable *)Nsn_Malloc(sizeof(nsn_symtable));
    st->symbols = NULL;
    st->count = 0;
    st->capacity = 0;
    return st;
}

void NsnSymtable_Add(nsn_symtable *st, const char *name, int type) {
    if (st->count >= st->capacity) {
        st->capacity = st->capacity ? st->capacity * 2 : 16;
        st->symbols = realloc(st->symbols, st->capacity * sizeof(nsn_symbol));
    }
    st->symbols[st->count].name = Nsn_StrDup(name);
    st->symbols[st->count].type = type;
    st->count++;
}

void NsnSymtable_Free(nsn_symtable *st) {
    for (int i = 0; i < st->count; i++) {
        Nsn_Free(st->symbols[i].name);
    }
    Nsn_Free(st->symbols);
    Nsn_Free(st);
}
