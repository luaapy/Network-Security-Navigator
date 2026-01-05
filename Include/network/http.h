/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * HTTP client
 */

#ifndef NSN_NETWORK_HTTP_H
#define NSN_NETWORK_HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nsn.h"

/* Simple HTTP GET request. Returns an NSN object representing the response (e.g., a dict or string). */
nsn_object *nsn_http_get(const char *url);

/* HTTP POST request with optional body data. */
nsn_object *nsn_http_post(const char *url, nsn_object *data);

/* Additional HTTP methods could be added (PUT, DELETE, etc.) */

#ifdef __cplusplus
}
#endif

#endif // NSN_NETWORK_HTTP_H
