#ifndef I2P_DATATYPES_ROUTER_INFO_H
#define I2P_DATATYPES_ROUTER_INFO_H
#include <i2p/datatypes/identity.h>

struct i2p_router_address;

struct i2p_router_info
{
  struct i2p_identity identity;
};


int i2p_router_info_parse(struct i2p_router_info * ri, uint8_t ** buf, size_t sz);


#endif
