/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Core interpreter state
 */

#ifndef NSN_INTERNAL_STATE_H
#define NSN_INTERNAL_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "object.h"
#include "memory.h"
#include "error.h"
#include "vm.h"

/* Global interpreter state structure */
typedef struct _nsn_interpreter_state {
    /* Memory arena for object allocation */
    nsn_arena *arena;
    
    /* Thread state (single-threaded for now) */
    struct _nsn_thread_state *thread;
    
    /* Modules cache */
    nsn_object *modules_dict; /* dict of imported modules */
    
    /* Built-in types */
    nsn_type *type_type;
    nsn_type *int_type;
    nsn_type *float_type;
    nsn_type *bool_type;
    nsn_type *string_type;
    nsn_type *list_type;
    nsn_type *dict_type;
    nsn_type *function_type;
    nsn_type *module_type;
    nsn_type *ipaddr_type;
    nsn_type *network_type;
    
    /* Exception objects */
    nsn_object *exc_base;
    nsn_object *exc_exception;
    nsn_object *exc_typeerror;
    nsn_object *exc_valueerror;
    nsn_object *exc_importerror;
    nsn_object *exc_runtimeerror;
    nsn_object *exc_memoryerror;
    nsn_object *exc_systemerror;
    nsn_object *exc_networkerror;
    nsn_object *exc_securityerror;
    
    /* Current exception state */
    nsn_object *current_exception_type;
    nsn_object *current_exception_value;
    nsn_object *current_exception_traceback;
} nsn_interpreter_state;

/* Retrieve the global interpreter state (singleton) */
nsn_interpreter_state *Nsn_GetInterpreterState(void);

/* Initialize and finalize interpreter state */
int Nsn_State_Initialize(void);
void Nsn_State_Finalize(void);

#ifdef __cplusplus
}
#endif

#endif // NSN_INTERNAL_STATE_H
