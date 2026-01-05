#include "nsn.h"
#include "core/object.h"

/*
 * NSN Iteration Tools
 */

typedef struct {
    nsn_object base;
    nsn_object *obj;
    int index;
} nsn_iterator_object;

static void iter_dealloc(nsn_object *op) {
    nsn_iterator_object *io = (nsn_iterator_object *)op;
    nsn_decref(io->obj);
    free(io);
}

nsn_type nsn_IteratorType = {
    .name = "iterator",
    .basicsize = sizeof(nsn_iterator_object),
    .dealloc = iter_dealloc
};

nsn_object *nsn_get_iter(nsn_object *obj) {
    /* Create iterator for list, dict, range, etc. */
    return NULL;
}

nsn_object *nsn_iter_next(nsn_object *iter) {
    /* Return next item or NULL if done */
    return NULL;
}
