#include <i2p/cryptoimpl/openssl.h>


struct i2p_crypto_openssl_st
{
  struct i2p_allocator * alloc;
};

void i2p_crypto_openssl_singlethreaded(struct i2p_crypto * crypto, struct i2p_allocator * alloc)
{
  struct i2p_crypto_openssl_st * impl = NULL;
  impl = alloc->alloc(alloc, sizeof(struct i2p_crypto_openssl_st));
  impl->alloc = alloc;



  crypto->impl = impl;
}
