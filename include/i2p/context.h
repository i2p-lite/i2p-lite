#ifndef I2P_CONTEXT_H
#define I2P_CONTEXT_H
#include <i2p/crypto.h>
#include <i2p/netdb.h>
#ifdef __cplusplus
extern "C" {
#endif
struct i2p_main_context
{
  struct i2p_allocator * mem;
  struct i2p_crypto crypto;
  struct i2p_netdb * netdb;
};

void i2p_main_init(struct i2p_main_context * ctx);

#ifdef __cplusplus
}
#endif

#endif
