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
  memcpy(m+33, op->buff, 222);
  // hash it
  SHA256(m+33, sizeof(op->buff), m + 1);
  // calc b = b1*m % p
  BN_bin2bn(m, 255, b);
  BN_mod_mul(b, b1, b, impl->elgp, ctx);

  bn2buf(a, op->buff, 256);
  bn2buf(b, op->buff + 256, 256);

  BN_CTX_free(ctx);

  if(op->result)
  {
      op->result(op);
  }
}

void i2p_openssl_elg_decrypt(struct i2p_crypto * crypto, struct elg_op * op)
{
  struct i2p_cryptoimpl_openssl_st * impl = (struct i2p_cryptoimpl_openssl_st *) crypto->impl;
  BN_CTX * ctx = BN_CTX_new();
  BIGNUM * x = BN_CTX_get (ctx), * a = BN_CTX_get (ctx), * b = BN_CTX_get (ctx);
  BN_bin2bn (op->key, 256, x);
  BN_sub (x, impl->elgp, x); BN_sub_word (x, 1); // x = elgp - x- 1
  BN_bin2bn (op->buff, 256, a);
  BN_bin2bn (op->buff + 256, 256, b);
  // m = b*(a^x mod p) mod p
  BN_mod_exp (x, a, x, impl->elgp, ctx);
  BN_mod_mul (b, b, x, impl->elgp, ctx);
  uint8_t m[255];
  bn2buf (b, m, 255);
  BN_CTX_free (ctx);
  uint8_t hash[32];
  SHA256 (m + 33, 222, hash);
  if (memcmp (m + 1, hash, 32))
	{
    /* fail decrypt */
    op->success = 0;
  }
  else
  {
    op->success = 1;
    memcpy (op->buff, m + 33, 222);
  }
  if(op->result)
  {
    op->result(op);
  }
}


void i2p_openssl_elg_keygen(struct i2p_crypto * crypto, struct elg_keygen_op * op)
{
  struct i2p_cryptoimpl_openssl_st * impl = (struct i2p_cryptoimpl_openssl_st *) crypto->impl;
  BN_CTX * ctx = BN_CTX_new ();
  BIGNUM * p = BN_new ();

  crypto->randbytes(crypto, op->priv, 256);
  BN_bin2bn (op->priv, 256, p);
  BN_mod_exp (p, impl->elgg, p, impl->elgp, ctx);
  bn2buf (p, op->pub, 256);
  BN_free (p);
  BN_CTX_free (ctx);
}
