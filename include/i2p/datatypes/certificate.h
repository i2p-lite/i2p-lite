#ifndef I2P_DATATYPES_CERTIFICATE_H
#define I2P_DATATYPES_CERTIFICATE_H
#include <stdlib.h>

struct i2p_certificate
{
  uint8_t * data;
  size_t size;
};

#endif
