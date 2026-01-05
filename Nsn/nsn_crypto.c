/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: nsn_crypto.c
 * Description: Internal cryptography support logic.
 */

#include "nsn.h"
#include <openssl/rand.h>

int NsnCrypto_Init(void) {
    /* Initialize OpenSSL or internal crypto state */
    return 0;
}

int NsnCrypto_RandomBytes(unsigned char *buf, int len) {
    return RAND_bytes(buf, len);
}
