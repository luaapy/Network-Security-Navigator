/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: frozen.c
 * Description: Logic for loading frozen modules.
 */

#include "nsn.h"
#include "frozen_modules/importlib.h"
#include <string.h>

int NsnFrozen_IsFrozen(const char *name) {
    for (int i = 0; _nsn_frozen_modules[i].name != NULL; i++) {
        if (strcmp(name, _nsn_frozen_modules[i].name) == 0) {
            return 1;
        }
    }
    return 0;
}

nsn_object *NsnFrozen_LoadModule(const char *name) {
    for (int i = 0; _nsn_frozen_modules[i].name != NULL; i++) {
        if (strcmp(name, _nsn_frozen_modules[i].name) == 0) {
            /* 
             * 1. Create a module object
             * 2. Execute the frozen bytecode in the module's scope
             * 3. Return the module object
             */
            nsn_object *m = nsn_module_new(name);
            // Nsn_ExecuteBytecode(_nsn_frozen_modules[i].code, _nsn_frozen_modules[i].size, m);
            return m;
        }
    }
    return NULL;
}
