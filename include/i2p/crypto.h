#ifndef I2P_CRYPTO_H
#define I2P_CRYPTO_H

#include <stdint.h>
#include <stdlib.h>
#include <i2p/ipc.h>
#include <i2p/memory.h>

#define ELG_PLAINTEXT_SIZE 222

/** elgamal key buffer */
typedef uint8_t elg_keybuffer[256];

/** elgamal data buffer */
typedef uint8_t elg_buffer[514];

/** encrypt/decrypt in place with elgamal event */
struct elg_op
{
  void * userdata;
  void (*result)(struct elg_op *);
  int success;
  elg_keybuffer key;
  elg_buffer buff;
};

/** elgamal key generation event */
struct elg_keygen_op
{
  void * userdata;
  void (*result)(struct elg_keygen_op *);
  elg_keybuffer priv;
  elg_keybuffer pub;
};

void elg_put_buffer(elg_buffer *dst, const uint8_t * src, size_t sz);

/** sha256 hash digest */
typedef uint8_t sha256_digest_t[32];

/** sha256 hash event */
struct sha256_op
{
  void * userdata;
  void (*result)(struct sha256_op *);
  const uint8_t * buff;
  size_t sz;
  sha256_digest_t digest;
};

/** sha1 hash digest */
typedef uint8_t sha1_digest_t[20];

/** sha1 hash event */
struct sha1_op
{
  void * userdata;
  void (*result)(struct sha1_op *);
  const uint8_t * buff;
  size_t sz;
  sha1_digest_t digest;
};

/** tunnel data message buffer */
typedef uint8_t i2p_tunnel_data[1028];

/** aes keybuffer */
typedef uint8_t aes_keybuffer[32];

/** aes iv buffer */
typedef uint8_t aes_iv[16];

/** tunnel aes encrypt/decrypt event in place */
struct aes_tunnel_op
{
  void * userdata;
  void (*result)(struct aes_tunnel_op *);
  aes_keybuffer layerkey;
  aes_iv layeriv;
  aes_keybuffer tunnelkey;
  aes_iv tunneliv;
  i2p_tunnel_data msg;
};

/** dh key exchange operation */
struct dh_op
{
  void * userdata;
  void (*result)(struct dh_op *);
  elg_keybuffer priv;
  elg_keybuffer pub;
  elg_keybuffer shared;
};

/** dsa privatey key buffer */
typedef uint8_t dsa_privkeybuffer[64];

/** dsa public key buffer */
typedef uint8_t dsa_pubkeybuffer[20];

/** dsa signature buffer */
typedef uint8_t dsa_sigbuffer[40];

struct dsa_verify_op
{
  void * userdata;
  void (*result)(struct dsa_verify_op *, int);
  dsa_pubkeybuffer key;
  const uint8_t * body;
  size_t sz;
  const uint8_t * sig;
};

struct dsa_sign_op
{
  void * userdata;
  void (*result)(struct dsa_sign_op *);
  dsa_privkeybuffer key;
  const uint8_t * body;
  size_t sz;
  dsa_sigbuffer sig;
};

/** ed25519 public key buffer */
typedef uint8_t eddsa_pubkeybuffer[32];

/** ed25519 private key buffer */
typedef uint8_t eddsa_privkeybuffer[32];

/** ed25519 signature buffer */
typedef uint8_t eddsa_sigbuffer[64];

/** eddsa signature verify operation */
struct eddsa_verify_op
{
  void * userdata;
  void (*result)(struct eddsa_verify_op *, int);
  const uint8_t * body;
  size_t sz;
  const uint8_t * sig;
  eddsa_pubkeybuffer key;
};

/** eddsa signer operation */
struct eddsa_sign_op
{
  void * userdata;
  void (*result)(struct eddsa_sign_op *);
  const uint8_t * body;
  size_t sz;
  eddsa_sigbuffer sig;
};

struct i2p_crypto
{
  /** private implementation */
  void * impl;
  void (*randbytes)(struct i2p_crypto *, uint8_t *, size_t);
  void (*elg_keygen)(struct i2p_crypto *, struct elg_keygen_op *);
  void (*elg_encrypt)(struct i2p_crypto *, struct elg_op *);
  void (*elg_decrypt)(struct i2p_crypto *, struct elg_op *);
  void (*elg_encrypt_padded)(struct i2p_crypto *, struct elg_op *);
  void (*elg_decrypt_padded)(struct i2p_crypto *, struct elg_op *);
  void (*sha256)(struct i2p_crypto *, struct sha256_op *);
  void (*sha1)(struct i2p_crypto *, struct sha1_op *);
  void (*tunnel_encrypt)(struct i2p_crypto *, struct aes_tunnel_op *);
  void (*tunnel_decrypt)(struct i2p_crypto *, struct aes_tunnel_op *);
  void (*dsa_sha1_verify)(struct i2p_crypto *, struct dsa_verify_op *);
  void (*dsa_sha1_sign)(struct i2p_crypto *, struct dsa_sign_op *);
  void (*eddsa_sha512_sign)(struct i2p_crypto *, struct eddsa_sign_op *);
  void (*eddsa_sha512_verify)(struct i2p_crypto *, struct eddsa_verify_op *);
};

#endif
