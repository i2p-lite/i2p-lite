#include <i2p/crypto.h>
#include <string.h>

void elg_put_buffer(elg_buffer * dst, const uint8_t * src, size_t sz)
{
  if(sz <= 222)
    memcpy(*dst, src, sz);
  else
    abort();
}
