#ifndef _HUB_
#define _HUB_
#include "msgbuffer.h"
#include "force_patch.h"
#include <chrono>
#include <sys/msg.h>
#include <stdio.h>
#include <iostream>

class hub {
public:
  int msgCount;
  int msqID;
  int size;
  int num_Active_Probes;
  pid_t hPID;
  pid_t aPID, bPID, cPID;
  long key;
  msgbuffer msgBuf;
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point t;

  hub();
  void sendReturnMsg();
  void rcvMsg();
  void showMessages();
  void deleteQ();
  void initialize();
  void idProbes();
  void performExit();
  long getTime();
};

#endif
