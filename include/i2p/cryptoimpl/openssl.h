#ifndef I2P_CRYPTOIMPL_OPENSSL_H
#define I2P_CRYPTOIMPL_OPENSSL_H

#include <i2p/crypto.h>
#include <openssl/bn.h>

/** initialize i2p crypto subsystem using openssl and no threading */
void i2p_crypto_openssl_singlethreaded(struct i2p_crypto *, struct i2p_allocator *);

struct i2p_cryptoimpl_openssl_st
{
  struct i2p_allocator * alloc;
  BIGNUM * elgp;
  BIGNUM * elgg;
};

void i2p_openssl_elg_encrypt(struct i2p_crypto *, struct elg_op *);
void i2p_openssl_elg_decrypt(struct i2p_crypto *, struct elg_op *);


#endif
