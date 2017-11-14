#include <i2p/memory.h>
#include <jemalloc/jemalloc.h>


struct i2p_allocator
{
  int unused;
};

void * i2p_alloc(struct i2p_allocator * a, size_t sz)
{
  (void) a;
  return mallocx(sz, MALLOCX_ZERO);
}

void i2p_free(struct i2p_allocator * a, void * ptr)
{
  (void) a;
  if(ptr) free(ptr);
}

struct i2p_allocator i2p_alloc_api;

void i2p_allocator_init(struct i2p_allocator ** api)
{
  *api = &i2p_alloc_api;
}
