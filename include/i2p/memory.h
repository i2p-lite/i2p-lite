#ifndef I2P_MEMORY_H
#define I2P_MEMORY_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

struct i2p_allocator;

void i2p_allocator_init(struct i2p_allocator **);

void * i2p_alloc(struct i2p_allocator *, size_t sz);
void i2p_free(struct i2p_allocator *, void * );
  
#ifdef __cplusplus
}
#endif

  
#endif
