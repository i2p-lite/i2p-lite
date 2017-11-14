#ifndef I2P_NETDB_H
#define I2P_NETDB_H
#include <i2p/datatypes/ident_hash.h>
#include <i2p/datatypes/router_info.h>
#include <i2p/memory.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

  struct i2p_netdb;

  bool i2p_netdb_new(struct i2p_netdb **, struct i2p_allocator *);
  bool i2p_netdb_free(struct i2p_netdb **);

  void i2p_netdb_set_root(struct i2p_netdb *, const char * rootdir);
  bool i2p_netdb_init_skiplist(struct i2p_netdb *);
  
  /** @brief iteratator type for visiting all of the netdb */
  struct i2p_netdb_iterator
  {
    void * user;
    struct i2p_netdb * netdb;
    bool (*filter)(struct i2p_netdb_iterator *, struct i2p_router_info *);
    void (*visit)(struct i2p_netdb_iterator *, struct i2p_router_info *);
  };

  bool i2p_netdb_iterate_local(struct i2p_netdb *, struct i2p_netdb_iterator *);

  struct i2p_router_info * i2p_netdb_load_local(struct i2p_netdb *, i2p_ident_hash target);
  bool i2p_netdb_store_local(struct i2p_netdb *, struct i2p_router_info *);
  
#ifdef __cplusplus
}
#endif
#endif
