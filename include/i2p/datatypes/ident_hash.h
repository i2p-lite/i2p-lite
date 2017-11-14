#ifndef I2P_DATATYPES_IDENT_HASH_H
#define I2P_DATATYPES_IDENT_HASH_H
#include <stdint.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

  typedef uint8_t i2p_ident_hash[32];
  
  ssize_t i2p_ident_hash_b64encode(i2p_ident_hash h, char * outbuf, size_t outsz);
  ssize_t i2p_ident_hash_b32encode(i2p_ident_hash h, char * outbuf, size_t outsz);

  ssize_t i2p_ident_hash_b64decode(i2p_ident_hash h, uint8_t * inbuf, size_t insz);
  ssize_t i2p_ident_hash_b32decode(i2p_ident_hash h, uint8_t * inbuf, size_t insz);
  
#ifdef __cplusplus
}
#endif

#endif
