#include <i2p/crypto.h>
#include <i2p/memory.h>

int main(int argc, char * argv[])
{
  struct i2p_allocator alloc;
  struct i2p_crypto crypto;

  i2p_allocator_init(&alloc);
  i2p_crypto_openssl_singlethreaded(&crypto, &alloc);

  return 0;
}
