#include "nsn.h"
#include "network/packet.h"
#include <stdio.h>

/*
 * NSN Packet Manipulation Module implementation
 */

typedef struct {
    nsn_object base;
    unsigned char *data;
    size_t length;
} nsn_packet_obj;

static void packet_dealloc(nsn_object *op) {
    nsn_packet_obj *p = (nsn_packet_obj *)op;
    free(p->data);
    free(p);
}

nsn_type nsn_PacketType = {
    .name = "packet",
    .basicsize = sizeof(nsn_packet_obj),
    .dealloc = packet_dealloc
};

nsn_object *nsn_packet_from_data(const unsigned char *data, size_t len) {
    nsn_packet_obj *p = malloc(sizeof(nsn_packet_obj));
    p->base.ref_count = 1;
    p->base.type = &nsn_PacketType;
    p->data = malloc(len);
    memcpy(p->data, data, len);
    p->length = len;
    return (nsn_object *)p;
}

nsn_object *nsn_packet_get_payload(nsn_object *p) {
    /* Return payload as bytes object */
    return NULL;
}
