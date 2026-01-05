#include "nsn.h"
#include "network/http.h"
#include "network/tcp.h"
#include <stdio.h>
#include <string.h>

/*
 * NSN HTTP Module Implementation
 */

nsn_object *nsn_http_request(const char *method, const char *url, nsn_object *headers, nsn_object *data) {
    printf("HTTP %s Request to %s\n", method, url);
    /* 1. Parse URL to get host and path */
    /* 2. TCP connect to host:80/443 */
    /* 3. Send HTTP request line and headers */
    /* 4. Recv response and parse */
    return nsn_string_from_cstring("HTTP Response Body Placeholder");
}

nsn_object *nsn_http_get(const char *url) {
    return nsn_http_request("GET", url, NULL, NULL);
}

nsn_object *nsn_http_post(const char *url, nsn_object *data) {
    return nsn_http_request("POST", url, NULL, data);
}
