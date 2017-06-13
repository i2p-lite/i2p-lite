#ifndef I2P_IPC_H
#define I2P_IPC_H
// provides an inter process communication api so that components can talk to each other


struct i2p_ipc_api;
struct i2p_ipc;

/** ipc event parameters */
struct i2p_ipc_event
{
  /** the ipc context that issued the callback and will handle result */
  struct i2p_ipc * caller;
  /** user data for work and callback */
  void * userdata;
  /** the function that does work with userdata and returns the result of the work that was done */
  void * (*work)(void *);
  /** handle result from an event, with userdata and call result */
  void (*callback)(void *, void *);
};

/** ipc context */
struct i2p_ipc
{
  /** private implementation */
  void * impl;

  /** run ipc context mainloop, blocking */
  void (*run)(struct i2p_ipc *);

  /** stop ipc context mainloop */
  void (*stop)(struct i2p_ipc *);

  /**
     trigger new ipc event calling on another ipc context and informing the result via the context in the event callbacks
     returns -1 on failure to call, otherwise returns 0
  */
  int (*call)(struct i2p_ipc * other, struct i2p_ipc_event ev);

};


/** public api for creating ipc contexts */
struct i2p_ipc_api
{

  /** private implementation */
  void * impl;

  /** allocate new ipc context */
  struct i2p_ipc * (*alloc)(struct i2p_ipc_api *);

  /** free existing ipc context */
  void (*free)(struct i2p_ipc_api *, struct i2p_ipc **);

};

#endif
