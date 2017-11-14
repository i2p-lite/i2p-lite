#include <i2p/datatypes/router_info.h>
#include <i2p/memory.hpp>

struct i2p_router_info
{
  struct i2p_identity * ident;
  mem::buffer<uint8_t> sig;
};

bool i2p_router_info_parse(struct i2p_router_info ** ri, uint8_t ** buf, size_t sz)
{
  return false;
}

void i2p_router_info_free(struct i2p_router_info ** ri)
{
}
