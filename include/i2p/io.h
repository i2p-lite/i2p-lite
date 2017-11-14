#ifndef I2P_IO_H
#define I2P_IO_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAX_HOSTNAME_LEN
#define MAX_HOSTNAME_LEN 256
#endif

struct i2p_io_api;
struct i2p_io;

/** iterator for iterating over a list of sockaddrs */
struct i2p_sockaddr_iter
{
  void * userdata;
  /** iterate to next sockaddr, calls with null sockaddr when iteration is done */
  void (*next)(const struct sockaddr *, void *);
};

/** iterate over all sockaddr iterator results */
void i2p_sockaddr_iterate(struct i2p_sockaddr_iter *);

/** dns lookup event */
struct i2p_nslookup
{
  /** parent io context */
  struct i2p_io * io;

  /** private implementation */
  void * impl;

  /** user data */
  void * userdata;

  /** name to look up, null terminated */
  char hostname[MAX_HOSTNAME_LEN];
  /** port to put in sockaddr result */
  int port;

  /** get result iterator for successfully resolved addresses */
  struct i2p_sockaddr_iter * (*result_iter)(struct i2p_nslookup *);

  /** handle result of successful resolve */
  void (*resolved)(struct i2p_nslookup *);

  /** handle lookup timeout */
  void (*timeout)(struct i2p_nslookup *);

  /** handle lookup error */
  void (*error)(struct i2p_nslookup *);

};


struct i2p_tcp_client
{
  /** parent io context */
  struct i2p_io * io;

  /** private implementation */
  void * impl;

  /** opaque user data */
  void * userdata;

  /** remote address to connect to */
  struct sockaddr * remoteaddr;

  /** callback for successful connect */
  void (*connected)(struct i2p_tcp_client *);

  /** callback for connect timeout */
  void (*timeout)(struct i2p_tcp_client *);

  /** callback for connection refused*/
  void (*refused)(struct i2p_tcp_client *);

  /** callback for misc error when connecting*/
  void (*error)(struct i2p_tcp_client *, int);

};


struct i2p_net_io
{
  void * impl;


  void (*connect)(struct i2p_net_io*, struct i2p_tcp_client *);

};

struct i2p_netio_api
{
  void * impl;

  struct i2p_net_io * (*alloc)(struct i2p_netio_api *);
  void (*free)(struct i2p_netio_api *, struct i2p_net_io **);
};

#ifdef __cplusplus
}
#endif


#endif
