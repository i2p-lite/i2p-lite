#include <i2p/util.h>
#include <zlib.h>

const size_t ZLIB_CHUNK_SIZE = 16384;

struct i2p_zlib
{
  z_stream z;
  struct i2p_allocator * mem;
};

void i2p_zlib_init(struct i2p_zlib ** z, struct i2p_allocator * mem)
{
  (*z) = (struct i2p_zlib *) i2p_alloc(mem, sizeof(struct i2p_zlib));
  inflateInit2(&(*z)->z, MAX_WBITS + 16);
  (*z)->mem = mem;
}

void i2p_zlib_free(struct i2p_zlib ** z)
{
  struct i2p_allocator * mem = (*z)->mem;
  inflateEnd(&(*z)->z);
  i2p_free(mem, (*z));
  *z = NULL;
}

ssize_t i2p_zlib_decompress(struct i2p_zlib * z, uint8_t * inbuf, size_t insz, uint8_t * outbuf, size_t outsz)
{
  int err;
  z->z.next_in = inbuf;
  z->z.avail_in = insz;
  z->z.next_out = outbuf;
  z->z.avail_out = outsz;
  err = deflate(&z->z, Z_FINISH);
  ssize_t ret = outsz - z->z.avail_out;
  deflateReset(&z->z);
  if(err != Z_STREAM_END)
  {
    ret = -1;
  }
  return ret;
}
