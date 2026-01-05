#include "nsn.h"
#include "network/socket.h"
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

/*
 * NSN Socket Object Implementation
 */

typedef struct {
    nsn_object base;
    int fd;
    int family;
    int type;
    int proto;
} nsn_socket_object;

static void socket_dealloc(nsn_object *op) {
    nsn_socket_object *so = (nsn_socket_object *)op;
    if (so->fd != -1) {
#ifdef WIN32
        closesocket(so->fd);
#else
        close(so->fd);
#endif
    }
    free(so);
}

nsn_type nsn_SocketType = {
    .name = "socket",
    .basicsize = sizeof(nsn_socket_object),
    .dealloc = socket_dealloc
};

nsn_object *nsn_socket_new(int family, int type, int proto) {
    nsn_socket_object *so = malloc(sizeof(nsn_socket_object));
    so->base.ref_count = 1;
    so->base.type = &nsn_SocketType;
    so->family = family;
    so->type = type;
    so->proto = proto;
    so->fd = socket(family, type, proto);
    return (nsn_object *)so;
}

int nsn_socket_connect(nsn_object *socket, const char *host, int port) {
    nsn_socket_object *so = (nsn_socket_object *)socket;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &addr.sin_addr);
    
    return connect(so->fd, (struct sockaddr *)&addr, sizeof(addr));
}

int nsn_socket_send(nsn_object *socket, const char *data, size_t len) {
    nsn_socket_object *so = (nsn_socket_object *)socket;
    return send(so->fd, data, (int)len, 0);
}

int nsn_socket_recv(nsn_object *socket, char *buf, size_t len) {
    nsn_socket_object *so = (nsn_socket_object *)socket;
    return recv(so->fd, buf, (int)len, 0);
}
