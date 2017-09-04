#include <i2p/context.h>
#include <i2p/cryptoimpl/openssl.h>

void i2p_main_init(struct i2p_main_context * ctx)
{
  i2p_allocator_init(&ctx->mem);
  i2p_crypto_openssl_singlethreaded(&ctx->crypto, &ctx->mem);
}
