#ifndef I2P_CRYPTO_H
#define I2P_CRYPTO_H

#include <stdlib.h>
#include <i2p/ipc.h>

/** elgamal key buffer */
typedef uint8_t elg_keybuffer[256];

/** elgamal data buffer for normal elgamal */
typedef uint8_t elg_buffer[255];

/** elgamal data buffer for zeropadded elgamal */
typedef uint8_t elg_zeropad_buffer[514];

/** encrypt/decrypt with elgamal event */
struct elg_op
{
  void * userdata;
  elg_keybuffer * key;
  elg_buffer * buff;
  elg_zeropad_buffer * zp_buff;
  void (*result)(struct elg_op *);
};

/** sha256 hash digest */
typedef uint8_t sha256_digest_t[32];

/** sha256 hash event */
struct sha256_op
{
  void * userdata;
  uint8_t * buff;
  size_t sz;
  void (*result)(struct sha256_op *, sha256_digest_t);
};

/** sha1 hash digest */
typedef uint8_t sha1_digest_t[20];

/** sha1 hash event */
struct sha1_op
{
  void * userdata;
  uint8_t * buff;
  size_t sz;
  void (*result)(struct sha1_op *, sha1_digest_t);
};

/** tunnel data message buffer */
typedef uint8_t i2p_tunnel_data[1028];

/** aes keybuffer */
typedef uint8_t aes_keybuffer[32];

/** tunnel aes encrypt/decrypt event in place */
struct aes_tunnel_op
{
  void * userdata;
  aes_keybuffer * key;
  i2p_tunnel_data * msg;
  void (*result)(struct aes_tunnel_op *);
};

/** dh key exchange operation */
struct dh_op
{
  void * userdata;
  elg_keybuffer * priv;
  elg_keybuffer * pub;
  void (*result)(struct dh_op *, elg_keybuffer);
};

struct i2p_crypto
{
  /** private implementation */
  void * impl;

  void (*elg_encrypt)(struct i2p_crypto *, struct elg_op *);
  void (*elg_decrypt)(struct i2p_crypto *, struct elg_op *);
  void (*sha256)(struct i2p_crypto *, struct sha256_op *);
  void (*sha1)(struct i2p_crypto *, struct sha1_op *);
  void (*tunnel_encrypt)(struct i2p_crypto *, struct aes_tunnel_op *);
  void (*tunnel_decrypt)(struct i2p_crypto *, struct aes_tunnel_op *);
};


void i2p_crypto_openssl(struct i2p_crypto *, struct i2p_ipc *, struct i2p_allocator *);

#endif
