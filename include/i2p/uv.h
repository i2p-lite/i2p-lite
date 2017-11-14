#ifndef I2P_UV_H
#define I2P_UV_H

#include <i2p/io.h>
#include <i2p/ipc.h>
#include <i2p/threadpool.h>
#include <i2p/memory.h>
#include <uv.h>

#ifdef __cplusplus
extern "C" {
#endif


/** init ipc implemention using libuv */
void i2p_libuv_ipc_api(struct i2p_ipc_api *, struct i2p_allocator *);
/** init io implementation using libuv */
void i2p_libuv_netio_api(struct i2p_netio_api *, struct i2p_allocator *);
/** init threadpoool implementation using libuv */
void i2p_libuv_threadpool_api(struct i2p_threadpool_api *, struct i2p_allocator *);

#ifdef __cplusplus
}
#endif

  
#endif
