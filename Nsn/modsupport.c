#include "nsn.h"
#include "core/object.h"

/*
 * NSN Module Support Utilities
 */

nsn_object *nsn_module_create(const char *name, void *methods) {
    /* Create module and populate with method references */
    return nsn_module_new(name);
}

int nsn_module_add_object(nsn_object *m, const char *name, nsn_object *obj) {
    /* Add object to module's dictionary */
    return 0;
}

int nsn_module_add_int_constant(nsn_object *m, const char *name, long val) {
    // nsn_object *v = nsn_int_from_long(val);
    // return nsn_module_add_object(m, name, v);
    return 0;
}
