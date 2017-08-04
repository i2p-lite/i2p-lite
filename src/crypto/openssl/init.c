#include <i2p/cryptoimpl/openssl.h>
#include <string.h>

struct i2p_crypto_openssl_st
{
  struct i2p_allocator * alloc;
};

void i2p_crypto_openssl_singlethreaded(struct i2p_crypto * crypto, struct i2p_allocator * alloc)
{
  struct i2p_crypto_openssl_st * impl = NULL;
  impl = alloc->alloc(alloc, sizeof(struct i2p_crypto_openssl_st));
  impl->alloc = alloc;

  /* zero out function pointers */
  memset(crypto, 0, sizeof(struct i2p_crypto));

  crypto->impl = impl;
}
