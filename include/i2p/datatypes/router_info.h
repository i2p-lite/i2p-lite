#ifndef I2P_DATATYPES_ROUTER_INFO_H
#define I2P_DATATYPES_ROUTER_INFO_H
#include <i2p/datatypes/identity.h>

#ifdef __cplusplus
extern "C" {
#endif


struct i2p_router_address;

struct i2p_router_info;


bool i2p_router_info_parse(struct i2p_router_info ** ri, uint8_t ** buf, size_t sz);
struct i2p_identity * i2p_router_info_get_identity(struct i2p_router_info * ri);

  void i2p_router_info_free(struct i2p_router_info ** ri);

#ifdef __cplusplus
}
#endif

#endif
