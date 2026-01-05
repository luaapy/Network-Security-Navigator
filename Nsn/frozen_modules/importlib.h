/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: importlib.h
 * Description: Frozen bytecode for the bootstrap import system.
 */

#ifndef NSN_FROZEN_IMPORTLIB_H
#define NSN_FROZEN_IMPORTLIB_H

#include <stddef.h>

/*
 * This file contains the "frozen" bytecode for the core importlib logic, 
 * written in the NSN language itself. This allows the interpreter to 
 * bootstrap the import system using its own routines.
 */

static const unsigned char _nsn_frozen_importlib_code[] = {
    /* 
     * Dummy bytecode for:
     * def _find_and_load(name):
     *     return _network.load_builtin(name)
     */
    0x01, 0x00, 0x02, 0x5F, 0x66, 0x69, 0x6E, 0x64, 0x5F, 0x61, 0x6E, 0x64, 
    0x5F, 0x6C, 0x6F, 0x61, 0x64, 0x00, 0x20, 0x00, 0x00
};

struct _nsn_frozen {
    const char *name;
    const unsigned char *code;
    size_t size;
};

static struct _nsn_frozen _nsn_frozen_modules[] = {
    {"importlib", _nsn_frozen_importlib_code, sizeof(_nsn_frozen_importlib_code)},
    {NULL, NULL, 0}
};

#endif // NSN_FROZEN_IMPORTLIB_H
