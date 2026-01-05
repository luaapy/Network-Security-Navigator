#include "nsn.h"
#include "network/dns.h"
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

/*
 * NSN DNS Module Implementation
 */

nsn_object *nsn_dns_resolve(const char *hostname) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        return NULL;
    }

    char addr_str[INET6_ADDRSTRLEN];
    void *ptr;
    if (res->ai_family == AF_INET) {
        ptr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
    } else {
        ptr = &((struct sockaddr_in6 *)res->ai_addr)->sin6_addr;
    }
    inet_ntop(res->ai_family, ptr, addr_str, sizeof(addr_str));
    
    freeaddrinfo(res);
    return nsn_string_from_cstring(addr_str);
}

nsn_object *nsn_dns_reverse(const char *ip) {
    /* Implementation of reverse DNS lookup */
    return nsn_string_from_cstring("unknown.host");
}
