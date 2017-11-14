#include <i2p/datatypes/certificate.h>

struct i2p_certificate
{
  i2p_cert_type_t t;
  uint8_t * data;
  i2p_cert_size_t sz;
  i2p_allocator * mem;
};

bool i2p_cert_read(struct i2p_certificate ** cert, struct i2p_allocator * mem, uint8_t ** buf, size_t sz)
{
  *cert = (i2p_certificate *) i2p_alloc(mem, sizeof(i2p_certificate));
  (*cert)->mem = mem;
  bool ret = false;
  uint8_t * inbuf = *buf;
  switch(inbuf[0]) {
  case eCertType_NULL:
    (*cert)->t = eCertType_NULL;
    (*cert)->data = nullptr;
    (*cert)->sz = 0;
    inbuf += 3;
    ret = true;
  default:
    ;
  }
  *buf = inbuf;
  return ret;
}

void i2p_cert_free(struct i2p_certificate ** cert)
{
  i2p_allocator * mem = (*cert)->mem;
  i2p_free(mem, (*cert)->data);
  i2p_free(mem, *cert);
  *cert = nullptr;
}

int i2p_cert_type(struct i2p_certificate * cert)
{
  return cert->t;
}

bool i2p_cert_data(struct i2p_certificate * cert, uint8_t ** data, i2p_cert_size_t * sz)
{
  *data = cert->data;
  *sz = cert->sz;
  return true;
}

    
