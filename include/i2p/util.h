#ifndef I2P_UTIL_H
#define I2P_UTIL_H
#include <i2p/memory.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct i2p_zlib;

void i2p_zlib_init(struct i2p_zlib **, struct i2p_allocator *);
ssize_t i2p_zlib_decompress_chunk(struct i2p_zlib * z, const uint8_t * inbuf, size_t insz, uint8_t * outbuf, size_t outsz);
ssize_t i2p_zlib_compress_chunk(struct i2p_zlib * z, const uint8_t * inbuf, size_t inz, uint8_t * outbuf, size_t outsz);

void i2p_zlib_free(struct i2p_zlib **);


bool i2p_base64_encode(const uint8_t *, size_t, uint8_t *, size_t);
bool i2p_base64_decode(const uint8_t *, size_t, uint8_t *, size_t);

#ifdef __cplusplus
}
#endif 
#endif
