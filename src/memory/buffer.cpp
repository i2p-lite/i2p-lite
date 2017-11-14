#include <i2p/memory.hpp>
#include <stdint.h>

namespace mem
{
  void buffer_xor(buffer<uint8_t> & a, buffer<uint8_t> & b)
  {
    size_t idx = a._n;
    while(idx)
    {
      a._t[idx] ^= b._t[idx];
      --idx;
    }
  }
}
