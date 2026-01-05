#include "nsn.h"
#include <stdio.h>

/*
 * NSN SSH Client Module (requires libssh)
 */

typedef struct {
    nsn_object base;
    void *session; /* ssh_session */
} nsn_ssh_obj;

nsn_object *nsn_ssh_connect(const char *host, int port, const char *user) {
    printf("SSH Connecting to %s:%d as %s\n", host, port, user);
    /* libssh session init and connect */
    return NULL;
}

int nsn_ssh_auth_password(nsn_object *session, const char *password) {
    /* libssh password auth */
    return 0;
}

nsn_object *nsn_ssh_exec_command(nsn_object *session, const char *cmd) {
    /* libssh channel exec */
    return nsn_string_from_cstring("Command output placeholder");
}
