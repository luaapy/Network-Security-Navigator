/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: msvcrtmodule.c
 * Description: Interface to the Microsoft Visual C Runtime (MSVCRT).
 */

#include "nsn.h"
#ifdef _WIN32
#include <windows.h>
#include <conio.h>

static nsn_object *msvcrt_locking(nsn_object *self, nsn_object *args) {
    /* Implementation of _locking(fd, mode, nbytes) */
    return nsn_int_from_long(0);
}

static nsn_object *msvcrt_kbhit(nsn_object *self, nsn_object *args) {
    return nsn_bool_from_int(_kbhit());
}

static nsn_object *msvcrt_getch(nsn_object *self, nsn_object *args) {
    return nsn_int_from_long(_getch());
}

static nsn_method msvcrt_methods[] = {
    {"locking", msvcrt_locking},
    {"kbhit", msvcrt_kbhit},
    {"getch", msvcrt_getch},
    {NULL, NULL}
};

void _nsn_init_msvcrt(void) {
    nsn_object *m = nsn_module_new("msvcrt");
    // Register methods
}
#endif
