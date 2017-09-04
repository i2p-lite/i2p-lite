#include <i2p/cryptoimpl/openssl.h>
#include <string.h>
#include <openssl/rand.h>

// from i2pd

int bn2buf (BIGNUM * bn, uint8_t * buf, size_t len)
{
  int offset = len - BN_num_bytes (bn);
  if (offset < 0) return 0;
  BN_bn2bin (bn, buf + offset);
  memset (buf, 0, offset);
  return 1;
}

void i2p_openssl_randbytes(struct i2p_crypto * crypto, uint8_t * buf, size_t sz)
{
  (void) crypto;
  RAND_bytes(buf, sz);
}
