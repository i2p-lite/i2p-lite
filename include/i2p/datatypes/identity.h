#ifndef I2P_DATATYPES_IDENTITY_H
#define I2P_DATATYPES_IDENTITY_H
#include <stdlib.h>
#include <stdint.h>
#include <i2p/datatypes/certificate.h>

#ifdef __cplusplus
extern "C" {
#endif

  enum i2p_crypto_type_t
  {
    eCryptoTypeELG = 0,
    eCryptoTypeECIES = 1, // TODO: changeme
  };
  
  struct i2p_public_encrypt_key;

  ssize_t i2p_pubkey_encrypt(struct i2p_public_encrypt_key * k, uint8_t * inbuf, size_t insz, uint8_t * outbuf, size_t outsz);

  enum i2p_signing_type_t
  {
    eSigningType_DSA_SHA1 = 0,
    eSigningType_ECDSA_SHA256_P256 = 1,
    eSigningType_ECDSA_SHA384_P384 = 2,
    eSigningType_ECDSA_SHA512_P521 = 3,
    eSigningType_EDDSA_SHA512_ED25519 = 7
  };
  
  struct i2p_public_signing_key;

  bool i2p_pubkey_verify(struct i2p_public_signing_key * k, uint8_t * databuf, size_t datasz, uint8_t * sigbuf, size_t sigsz);
  
  struct i2p_identity;

  bool i2p_identity_parse(struct i2p_identity ** i, uint8_t ** buf, size_t sz);
  void i2p_identity_free(struct i2p_identity ** i);

  struct i2p_public_signing_key * i2p_identity_signing_pubkey(struct i2p_identity * i);
  struct i2p_public_encrypt_key * i2p_identity_encrypt_pubkey(struct i2p_identity * i);
  struct i2p_certificate * i2p_identity_certificate(struct i2p_identity * i);
  

#ifdef __cplusplus
}
#endif

  
#endif
