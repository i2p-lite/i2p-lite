#ifndef I2P_DATATYPES_CERTIFICATE_H
#define I2P_DATATYPES_CERTIFICATE_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <i2p/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

  enum i2p_cert_type_t
  {
    eCertType_NULL = 0,
    eCertType_HASHCASH = 1,
    eCertType_HIDDEN = 2,
    eCertType_SIGNED = 3,
    eCertType_MULTIPLE = 4,
    eCertType_KEY = 5
  };

  typedef uint16_t i2p_cert_size_t;
  
  struct i2p_certificate;

  bool i2p_cert_read(struct i2p_certificate ** cert, struct i2p_allocator * mem, uint8_t ** buf, size_t sz);
  void i2p_cert_free(struct i2p_certificate ** cert);

  int i2p_cert_type(struct i2p_certificate * cert);
  bool i2p_cert_data(struct i2p_certificate * cert, uint8_t ** data, i2p_cert_size_t * sz);

#ifdef __cplusplus
}
#endif

#endif
