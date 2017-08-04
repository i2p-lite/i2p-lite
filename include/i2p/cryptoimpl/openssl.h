#ifndef I2P_CRYPTOIMPL_OPENSSL_H
#define I2P_CRYPTOIMPL_OPENSSL_H

#include <i2p/crypto.h>

/** initialize i2p crypto subsystem using openssl and no threading */
void i2p_crypto_openssl_singlethreaded(struct i2p_crypto *, struct i2p_allocator *);


#endif
