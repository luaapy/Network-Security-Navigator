/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: sslmodule.c
 * Description: SSL/TLS socket wrapper implementation using OpenSSL.
 */

#include "nsn.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string.h>

/* --- SSL Object Logic --- */

typedef struct {
    NSN_OBJECT_HEAD
    SSL_CTX *ctx;
    SSL *ssl;
    nsn_object *sock;
} nsn_ssl_object;

static void ssl_dealloc(nsn_object *op) {
    nsn_ssl_object *so = (nsn_ssl_object *)op;
    if (so->ssl) {
        SSL_shutdown(so->ssl);
        SSL_free(so->ssl);
    }
    if (so->ctx) SSL_CTX_free(so->ctx);
    Nsn_XDECREF(so->sock);
    NsnMem_Free(so);
}

nsn_type Nsn_SSLType = {
    NSN_OBJECT_HEAD_INIT(&Nsn_TypeType)
    .tp_name = "_security.SSLSocket",
    .tp_basicsize = sizeof(nsn_ssl_object),
    .tp_dealloc = ssl_dealloc
};

/* --- Internal Helpers --- */

// Assuming nsn_socket_object is defined in network/socket.h
typedef struct { NSN_OBJECT_HEAD int fd; } nsn_socket_view;

/* --- Methods --- */

nsn_object *nsn_ssl_wrap_socket(nsn_object *sock) {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);
    if (!ctx) {
        NsnErr_SetString(NsnExc_SecurityError, "Failed to create SSL context");
        return NULL;
    }

    SSL *ssl = SSL_new(ctx);
    int fd = ((nsn_socket_view *)sock)->fd;
    SSL_set_fd(ssl, fd);

    if (SSL_connect(ssl) != 1) {
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        NsnErr_SetString(NsnExc_SecurityError, "SSL handshake failed");
        return NULL;
    }

    nsn_ssl_object *so = (nsn_ssl_object *)NsnMem_Malloc(sizeof(nsn_ssl_object));
    so->ob_refcnt = 1;
    so->ob_type = &Nsn_SSLType;
    so->ctx = ctx;
    so->ssl = ssl;
    Nsn_INCREF(sock);
    so->sock = sock;

    return (nsn_object *)so;
}

int nsn_ssl_send(nsn_object *ssl_obj, const char *data, size_t len) {
    nsn_ssl_object *so = (nsn_ssl_object *)ssl_obj;
    return SSL_write(so->ssl, data, (int)len);
}

int nsn_ssl_recv(nsn_object *ssl_obj, char *buf, size_t len) {
    nsn_ssl_object *so = (nsn_ssl_object *)ssl_obj;
    return SSL_read(so->ssl, buf, (int)len);
}

/* --- Module Setup --- */

void _nsn_init_ssl(void) {
    nsn_object *m = nsn_module_new("ssl");
}
