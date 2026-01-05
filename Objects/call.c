/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: call.c
 * Description: High-level function call dispatching.
 */

#include "nsn.h"

nsn_object *Nsn_CallFunction(nsn_object *callable, nsn_object **args, size_t nargs) {
    if (!callable) return NULL;
    
    /* 
     * In a real system, we'd check if the object has a tp_call slot.
     * For now, we'll assume it's a function object or a C function wrapper.
     */
    
    if (strcmp(callable->ob_type->tp_name, "function") == 0) {
        // Logic to create a new frame and call NsnVM_EvalFrame
        return nsn_eval_string("print('Calling user-defined function')"); // Placeholder
    }
    
    NsnErr_SetString(NsnExc_TypeError, "Object is not callable");
    return NULL;
}

nsn_object *Nsn_CallMethod(nsn_object *obj, const char *name, nsn_object **args, size_t nargs) {
    nsn_object *attr = NsnObject_GetAttr(obj, name);
    if (!attr) return NULL;
    
    nsn_object *res = Nsn_CallFunction(attr, args, nargs);
    Nsn_DECREF(attr);
    return res;
}
