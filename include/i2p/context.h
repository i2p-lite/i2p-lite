#ifndef I2P_CONTEXT_H
#define I2P_CONTEXT_H
#include <i2p/crypto.h>

struct i2p_main_context
{
  struct i2p_allocator mem;
  struct i2p_crypto crypto;
};

void i2p_main_init(struct i2p_main_context * ctx);

#endif
