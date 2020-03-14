#ifndef _MSGBUF_
#include <unistd.h>
#define _MSGBUF_

struct msgbuffer {
  long mtype;
  int msg;
  pid_t PID;
};

// Only used initially to associate each probe with a PID
struct IDbuffer {
  long mtype;
  pid_t PID;
};

#endif
