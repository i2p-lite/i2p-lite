#include <i2p/netdb.h>
#include <i2p/memory.hpp>
#include <i2p/datatypes/router_info.h>
#include <experimental/filesystem>
#include <cassert>
#include <iostream>
#include <fstream>

namespace fs = std::experimental::filesystem;

struct i2p_netdb
{
  mem::allocator mem;
  fs::path rootdir;

  bool Init()
  {
    fs::create_directories(rootdir);
    for (const char ch : "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890-~")
      if(!fs::create_directory(rootdir / fs::path("r"+std::string(&ch,1)))) return false;
    return fs::exists(rootdir);
  }

  bool Iterate(struct i2p_netdb_iterator * iter)
  {
    bool found = false;
    iter->netdb = this;
    for(auto & path : fs::recursive_directory_iterator(rootdir))
    {
      if(path.path().filename().string().find("routerInfo-") == 0)
      {
        std::ifstream i;
        i.open(path.path());
        if(i.is_open())
        {
          i.seekg(0, std::ios_base::end);
          size_t sz = i.tellg();
          i.seekg(0);
          {
            mem::buffer ribuf = mem.Alloc<uint8_t>(sz);
            uint8_t * buf = ribuf.data();
            i.read(reinterpret_cast<char*>(buf), sz);
            struct i2p_router_info * ri = nullptr;
            if(i2p_router_info_parse(&ri, &buf, sz))
            {
              if(iter->filter(iter, ri)) iter->visit(iter, ri);
              i2p_router_info_free(&ri);
            }
          }
        }
      }
    }
    iter->netdb = nullptr;
    return found;
  }
};

bool i2p_netdb_new(struct i2p_netdb ** n, struct i2p_allocator * mem)
{
  (*n) = (i2p_netdb*) i2p_alloc(mem, sizeof(i2p_netdb));
  (*n)->mem = mem;
  return true;
}

bool i2p_netdb_free(struct i2p_netdb ** n)
{
  if(*n)
  {
    i2p_free((*n)->mem, n);
    *n = nullptr;
    return true;
  }
  return false;
}

void i2p_netdb_set_root(struct i2p_netdb * netdb, const char * rootdir)
{
  netdb->rootdir = fs::path(rootdir);
}

bool i2p_netdb_init_skiplist(struct i2p_netdb * netdb)
{
  return netdb->Init();
}

bool i2p_netdb_iterate_local(struct i2p_netdb * netdb, struct i2p_netdb_iterator * iter)
{
  return netdb->Iterate(iter);
}
