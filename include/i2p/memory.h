#ifndef I2P_MEMORY_H
#define I2P_MEMORY_H
#include <stdlib.h>

/** i2p memory allocator interface */
struct i2p_allocator
{
  void * impl;
  void * (*alloc)(struct i2p_allocator *, size_t);
  void (*free)(struct i2p_allocator *, void *);
};

/** init function pointers into i2p allocator */
void i2p_allocator_init(struct i2p_allocator *);

#endif
