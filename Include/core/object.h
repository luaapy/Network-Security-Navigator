/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Object system
 */

#ifndef NSN_CORE_OBJECT_H
#define NSN_CORE_OBJECT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _object nsn_object;
typedef struct _typeobject nsn_type;

/* Object Head Macro */
#define NSN_OBJECT_HEAD \
    nsn_object *ob_next; \
    nsn_object *ob_prev; \
    long ob_refcnt; \
    nsn_type *ob_type;

/* Base Object Structure */
struct _object {
    NSN_OBJECT_HEAD
};

/* Type Object Structure */
struct _typeobject {
    NSN_OBJECT_HEAD
    const char *tp_name;
    size_t tp_basicsize;
    
    /* Standard Methods */
    void (*tp_dealloc)(nsn_object *);
    nsn_object *(*tp_repr)(nsn_object *);
    nsn_object *(*tp_str)(nsn_object *);
    long (*tp_hash)(nsn_object *);
};

/* Reference Counting Macros */
#define NSN_INCREF(op) (((nsn_object*)(op))->ob_refcnt++)
#define NSN_DECREF(op) do { \
    if (--((nsn_object*)(op))->ob_refcnt == 0) \
        ((nsn_object*)(op))->ob_type->tp_dealloc((nsn_object*)(op)); \
    } while (0)

#define NSN_XINCREF(op) do { if ((op) == NULL) ; else NSN_INCREF(op); } while (0)
#define NSN_XDECREF(op) do { if ((op) == NULL) ; else NSN_DECREF(op); } while (0)

/* Type Checking Macros */
#define Nsn_TYPE(ob) (((nsn_object*)(ob))->ob_type)

#ifdef __cplusplus
}
#endif

#endif // NSN_CORE_OBJECT_H
