#ifndef _PROBE_CHILD_
#define _PROBE_CHILD_
#include "probe.cpp"
#endif
#include "kill_patch.h"

class probeC : public probe {
public:
  int mTypeCounter;
  probeC() : probe(251, 'C'), mTypeCounter(300000){ probe::sendIDMsg('C'); }
  void initialize();
};

void probeC::initialize(){
  msgbuffer exitMsg;
  exitMsg.msg = -1;
  exitMsg.PID = this->PID;
  exitMsg.mtype = 8888888;
  kill_patch(msqID, (struct msgbuf *)&msgBuf, size, 8888888);

  while(true){ // Exited by kill_patch
    sendMsg(mTypeCounter, false);
    mTypeCounter++;
  }
}
