/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * Cryptography core header
 */

#ifndef NSN_SECURITY_CRYPTO_H
#define NSN_SECURITY_CRYPTO_H

#include "core/object.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RSA Primitives */
nsn_object *NsnCrypto_RSA_GenerateKey(int bits);
nsn_object *NsnCrypto_RSA_Encrypt(nsn_object *pubkey, nsn_object *data);
nsn_object *NsnCrypto_RSA_Decrypt(nsn_object *privkey, nsn_object *data);

/* Random Data */
nsn_object *NsnCrypto_GetRandomBytes(size_t len);

#ifdef __cplusplus
}
#endif

#endif // NSN_SECURITY_CRYPTO_H
