/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Error handling
 */

#ifndef NSN_CORE_ERROR_H
#define NSN_CORE_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Error setting functions */
void NsnErr_SetString(nsn_object *type, const char *message);
void NsnErr_SetObject(nsn_object *type, nsn_object *value);
void NsnErr_SetNone(nsn_object *type);

/* Error checking */
int NsnErr_Occurred(void);
void NsnErr_Clear(void);
void NsnErr_Fetch(nsn_object **ptype, nsn_object **pvalue, nsn_object **ptraceback);
void NsnErr_Restore(nsn_object *type, nsn_object *value, nsn_object *traceback);

/* Built-in exception types */
extern nsn_object *NsnExc_BaseException;
extern nsn_object *NsnExc_Exception;
extern nsn_object *NsnExc_TypeError;
extern nsn_object *NsnExc_ValueError;
extern nsn_object *NsnExc_ImportError;
extern nsn_object *NsnExc_RuntimeError;
extern nsn_object *NsnExc_MemoryError;
extern nsn_object *NsnExc_SystemError;
extern nsn_object *NsnExc_NetworkError; /* NSN specific */
extern nsn_object *NsnExc_SecurityError; /* NSN specific */

/* Convenience macros */
#define NsnErr_BadInternalCall() NsnErr_SetString(NsnExc_SystemError, "Bad internal call")
#define NsnErr_NoMemory() NsnErr_SetNone(NsnExc_MemoryError)

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_ERROR_H
