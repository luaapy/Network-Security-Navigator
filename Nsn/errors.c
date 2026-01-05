/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Error handling implementation
 */

#include "nsn.h"
#include <stdio.h>
#include <string.h>

/* Thread-local or global error state (simplified to global for now) */
typedef struct {
    nsn_object *type;
    nsn_object *value;
    nsn_object *traceback;
} NsnErrorState;

static NsnErrorState g_error_state = {NULL, NULL, NULL};

void NsnErr_SetObject(nsn_object *type, nsn_object *value) {
    Nsn_XDECREF(g_error_state.type);
    Nsn_XDECREF(g_error_state.value);
    
    Nsn_XINCREF(type);
    Nsn_XINCREF(value);
    
    g_error_state.type = type;
    g_error_state.value = value;
}

void NsnErr_SetString(nsn_object *type, const char *message) {
    nsn_object *msg_obj = nsn_string_from_cstring(message);
    NsnErr_SetObject(type, msg_obj);
    Nsn_DECREF(msg_obj);
}

void NsnErr_SetNone(nsn_object *type) {
    NsnErr_SetObject(type, Nsn_None);
}

int NsnErr_Occurred(void) {
    return g_error_state.type != NULL;
}

void NsnErr_Clear(void) {
    Nsn_XDECREF(g_error_state.type);
    Nsn_XDECREF(g_error_state.value);
    Nsn_XDECREF(g_error_state.traceback);
    
    g_error_state.type = NULL;
    g_error_state.value = NULL;
    g_error_state.traceback = NULL;
}

void NsnErr_Fetch(nsn_object **ptype, nsn_object **pvalue, nsn_object **ptraceback) {
    *ptype = g_error_state.type;
    *pvalue = g_error_state.value;
    *ptraceback = g_error_state.traceback;
    
    g_error_state.type = NULL;
    g_error_state.value = NULL;
    g_error_state.traceback = NULL;
}

void NsnErr_Restore(nsn_object *type, nsn_object *value, nsn_object *traceback) {
    NsnErr_Clear();
    g_error_state.type = type;
    g_error_state.value = value;
    g_error_state.traceback = traceback;
}

const char *Nsn_Err_GetMessage(void) {
    if (g_error_state.value && strcmp(g_error_state.value->ob_type->tp_name, "string") == 0) {
        return ((nsn_string_object*)g_error_state.value)->data;
    }
    return "Unknown error";
}
