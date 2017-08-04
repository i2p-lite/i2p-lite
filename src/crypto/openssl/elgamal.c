#include <i2p/cryptoimpl/openssl.h>
#include <string.h>
#include <openssl/sha.h>


#define ELG_FULL_EXPONENT_BITS 2048
#define ELG_FULL_EXPONENT_BYTES (ELG_FULL_EXPONENT_BITS/8)

void i2p_openssl_elg_encrypt(struct i2p_crypto * crypto, struct elg_op * op)
{

  struct i2p_cryptoimpl_openssl_st * impl = (struct i2p_cryptoimpl_openssl_st *) crypto->impl;

  BN_CTX * ctx = BN_CTX_new();
  BIGNUM * k = BN_CTX_get(ctx);
  BIGNUM * y = BN_CTX_get(ctx);
  BIGNUM * b1 = BN_CTX_get(ctx);
  BIGNUM * b = BN_CTX_get(ctx);
  BIGNUM * a = BN_CTX_get(ctx);

  // rand k
  BN_rand(k, ELG_FULL_EXPONENT_BITS, -1, 1);
  // calc a
  BN_mod_exp(a, impl->elgg, k, impl->elgp, ctx);
  // key -> y
  BN_bin2bn(op->key, 256, y);
  // calc b1
  BN_mod_exp(b1, y, k, impl->elgp, ctx);

  // copy message in
  uint8_t m[255];
  m[0] = 0xff;
  memcpy(m+33, op->buff, sizeof(op->buff));
  // hash it
  SHA256(m+33, sizeof(op->buff), m + 1);
  // calc b = b1*m % p
  BN_bin2bn(m, 255, b);
  BN_mod_mul(b, b1, b, impl->elgp, ctx);

  bn2buf(a, op->result_buff, 256);
  bn2buf(b, op->result_buff + 256, 256);

  BN_CTX_free(ctx);

  if(op->result)
    op->result(op);
}

void i2p_openssl_elg_decrypt(struct i2p_crypto * crypto, struct elg_op * op)
{

}
