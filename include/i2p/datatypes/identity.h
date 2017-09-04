#ifndef I2P_DATATYPES_IDENTITY_H
#define I2P_DATATYPES_IDENTITY_H
#include <stdlib.h>
#include <stdint.h>
#include <i2p/datatypes/certificate.h>

struct i2p_identity
{
  uint8_t * signingKeyBuff;
  size_t signingKeyLen;
  int signingKeyType;
  uint8_t * encryptionKeyBuff;
  size_t encryptionKeyLen;
  int encryptionKeyType;
  struct i2p_certificate cert;
};

int i2p_identity_parse(struct i2p_identity * i, uint8_t ** buf, size_t sz);

#endif
