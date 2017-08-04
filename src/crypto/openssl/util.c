#include <i2p/cryptoimpl/openssl.h>
#include <string.h>

// from i2pd

int bn2buf (BIGNUM * bn, uint8_t * buf, size_t len)
{
  int offset = len - BN_num_bytes (bn);
  if (offset < 0) return 0;
  BN_bn2bin (bn, buf + offset);
  memset (buf, 0, offset);
  return 1;
}
