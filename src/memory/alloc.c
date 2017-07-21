#include <i2p/memory.h>
#include <jemalloc/jemalloc.h>


struct i2p_alloc_impl
{
  int unused;
};

void * i2p_alloc(struct i2p_allocator * a, size_t sz)
{
  return mallocx(sz, MALLOCX_ZERO);
}

void i2p_free(struct i2p_allocator * a, void * ptr)
{
  free(ptr);
}

void i2p_allocator_init(struct i2p_allocator * api)
{
  api->alloc = i2p_alloc;
  api->free = i2p_free;
}
