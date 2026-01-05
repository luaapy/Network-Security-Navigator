/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: bltinmodule.c
 * Description: Core built-in functions available in the global namespace.
 */

#include "nsn.h"
#include <stdio.h>
#include <string.h>

/* --- Built-in Functions --- */

typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;

static nsn_object *builtin_print(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    
    for (int i = 0; i < list->size; i++) {
        nsn_object *obj = list->items[i];
        if (strcmp(obj->ob_type->tp_name, "string") == 0) {
            typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;
            printf("%s", ((nsn_string_object*)obj)->data);
        } else if (strcmp(obj->ob_type->tp_name, "int") == 0) {
            typedef struct { NSN_OBJECT_HEAD long lval; } nsn_int_object;
            printf("%ld", ((nsn_int_object*)obj)->lval);
        } else {
            printf("<%s object at %p>", obj->ob_type->tp_name, (void*)obj);
        }
        
        if (i < list->size - 1) printf(" ");
    }
    printf("\n");
    
    Nsn_INCREF(Nsn_None);
    return Nsn_None;
}

static nsn_object *builtin_len(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;
    
    nsn_object *obj = list->items[0];
    long length = 0;
    
    if (strcmp(obj->ob_type->tp_name, "list") == 0) {
        length = ((nsn_list_view *)obj)->size;
    } else if (strcmp(obj->ob_type->tp_name, "string") == 0) {
        typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;
        length = strlen(((nsn_string_object*)obj)->data);
    }
    
    return nsn_int_from_long(length);
}

static nsn_object *builtin_type(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) return NULL;
    
    return nsn_string_from_cstring(list->items[0]->ob_type->tp_name);
}

/* --- Module Setup --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method builtin_methods[] = {
    {"print", builtin_print},
    {"len", builtin_len},
    {"type", builtin_type},
    {NULL, NULL}
};

void _nsn_init_builtins(void) {
    nsn_object *m = nsn_module_new("__builtins__");
    // Register methods to the builtins dictionary...
}
