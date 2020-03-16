#ifndef _MSGBUF_
#include <unistd.h>
#define _MSGBUF_

struct msgbuffer {
  long mtype; // See README.txt for full list of mtype's used
  int msg; // The generated valid reading (-1 for signal messages)
  pid_t PID; // The PID of the sender
};

// Only used initially to associate each probe with a PID
struct IDbuffer {
  long mtype;
  pid_t PID;
};

#endif
