/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: getargs.c
 * Description: Logic for parsing C-extension function arguments.
 */

#include "nsn.h"
#include <stdarg.h>
#include <string.h>

/**
 * nsn_get_args(args, "si", &name, &age)
 * s: string
 * i: integer (long)
 * o: generic nsn_object
 * b: boolean
 */
int nsn_get_args(nsn_object *args, const char *format, ...) {
    if (args->ob_type != &Nsn_ListType) {
        NsnErr_SetString(NsnExc_TypeError, "Arguments must be a list");
        return 0;
    }

    size_t nargs = nsn_list_size(args);
    if (nargs < strlen(format)) {
        NsnErr_SetString(NsnExc_TypeError, "Missing required arguments");
        return 0;
    }

    va_list va;
    va_start(va, format);

    for (int i = 0; format[i] != '\0'; i++) {
        nsn_object *item = nsn_list_get_item(args, i);
        char c = format[i];

        switch (c) {
            case 's': {
                const char **out = va_arg(va, const char **);
                if (item->ob_type != &Nsn_StringType) {
                    NsnErr_SetString(NsnExc_TypeError, "Expected string");
                    goto fail;
                }
                *out = nsn_string_as_cstring(item);
                break;
            }
            case 'i': {
                long *out = va_arg(va, long *);
                if (item->ob_type != &Nsn_IntType) {
                    NsnErr_SetString(NsnExc_TypeError, "Expected integer");
                    goto fail;
                }
                *out = nsn_int_as_long(item);
                break;
            }
            case 'b': {
                int *out = va_arg(va, int *);
                if (item->ob_type != &Nsn_BoolType) {
                    NsnErr_SetString(NsnExc_TypeError, "Expected boolean");
                    goto fail;
                }
                *out = (item == Nsn_True);
                break;
            }
            case 'o': {
                nsn_object **out = va_arg(va, nsn_object **);
                *out = item;
                break;
            }
            default:
                NsnErr_SetString(NsnExc_RuntimeError, "Invalid format character in nsn_get_args");
                goto fail;
        }
    }

    va_end(va);
    return 1;

fail:
    va_end(va);
    return 0;
}
