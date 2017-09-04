#include <i2p/crypto.h>
#include <i2p/context.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
  /** init all subsystems */
  struct i2p_main_context ctx;
  i2p_main_init(&ctx);

  /** do crypto tests */
  struct i2p_crypto * crypto;
  crypto = &ctx.crypto;

  /** elg keygen */
  struct elg_keygen_op keygen = {
    .userdata = NULL,
    .result = NULL,
    .priv = {0},
    .pub = {0}
  };

  crypto->elg_keygen(crypto, &keygen);

  struct elg_op elg = {
    .userdata =NULL,
    .result = NULL,
    .success = 0,
    .key = {0},
    .buff = {0}
  };
  /** randomize payload */
  crypto->randbytes(crypto, elg.buff, ELG_PLAINTEXT_SIZE);
  /** copy pubkey */
  memcpy(elg.key, keygen.pub, sizeof(elg_keybuffer));

  /** encrypt */
  crypto->elg_encrypt(crypto, &elg);

  /** copy privkey */
  memcpy(elg.key, keygen.priv, sizeof(elg_keybuffer));

  /** decrypt */
  crypto->elg_decrypt(crypto, &elg);
  assert(elg.success);

  return 0;
}
