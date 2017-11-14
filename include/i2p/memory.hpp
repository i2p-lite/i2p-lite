#ifndef I2P_MEMORY_HPP
#define I2P_MEMORY_HPP
#include <i2p/memory.h>
#include <cassert>

namespace mem
{

  template<typename Buff>
  void buffer_xor(Buff & a, Buff & b);
  
  template<typename T>
  struct buffer
  {
    i2p_allocator * _mem;
    T * _t;
    size_t _n;

    T & operator [](std::size_t idx) { return _t[idx]; }
    buffer<T> & operator ^ (buffer<T> & other)
    {
      assert(_n == other._n);
      buffer_xor(*this, other);
      return *this;
    }

    T * data() { return _t; }

    buffer() : _mem(nullptr), _t(nullptr) {}
    buffer(i2p_allocator * m, T * t, size_t n) : _mem(m), _t(t), _n(n) {}
    ~buffer() { i2p_free(_mem, _t); }
  };
  
  struct allocator
  {

    allocator & operator = (i2p_allocator * mem)
    {
      _mem = mem;
      return *this;
    }
    
    struct i2p_allocator * _mem = nullptr;

    operator struct i2p_allocator * () { return _mem; }

    template<typename T>
    buffer<T> Alloc(std::size_t n=1)
    {
      T * t = reinterpret_cast<T *>(i2p_alloc(_mem, sizeof(T) * n));
      return buffer(_mem, t, n);
    }
  };
}



#endif
