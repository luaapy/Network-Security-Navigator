/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: winreg.c
 * Description: Windows Registry API implementation for NSN.
 */

#include "nsn.h"
#ifdef _WIN32
#include <windows.h>

static nsn_object *winreg_OpenKey(nsn_object *self, nsn_object *args) {
    /* TODO: Parse HKEY, subkey, sam */
    return Nsn_None;
}

static nsn_object *winreg_QueryValue(nsn_object *self, nsn_object *args) {
    /* TODO: Implement RegQueryValueEx */
    return nsn_string_from_cstring("registry_value_placeholder");
}

static nsn_method winreg_methods[] = {
    {"OpenKey", winreg_OpenKey},
    {"QueryValue", winreg_QueryValue},
    {NULL, NULL}
};

void _nsn_init_winreg(void) {
    nsn_object *m = nsn_module_new("winreg");
    nsn_module_add_object(m, "HKEY_CLASSES_ROOT", nsn_int_from_long((long)HKEY_CLASSES_ROOT));
    nsn_module_add_object(m, "HKEY_CURRENT_USER", nsn_int_from_long((long)HKEY_CURRENT_USER));
    nsn_module_add_object(m, "HKEY_LOCAL_MACHINE", nsn_int_from_long((long)HKEY_LOCAL_MACHINE));
    nsn_module_add_object(m, "HKEY_USERS", nsn_int_from_long((long)HKEY_USERS));
}
#endif
