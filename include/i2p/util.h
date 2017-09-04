#ifndef I2P_UTIL_H
#define I2P_UTIL_H
#include <i2p/memory.h>
#include <stdint.h>

struct i2p_zlib;

void i2p_zlib_init(struct i2p_zlib **, struct i2p_allocator *);
ssize_t i2p_zlib_decompress_chunk(struct i2p_zlib * z, const uint8_t * inbuf, size_t insz, uint8_t * outbuf, size_t outsz);
ssize_t i2p_zlib_compress_chunk(struct i2p_zlib * z, const uint8_t * inbuf, size_t inz, uint8_t * outbuf, size_t outsz);

void i2p_zlib_free(struct i2p_zlib **);

#endif
