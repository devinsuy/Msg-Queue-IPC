#ifndef _PROBE_CHILD_
#define _PROBE_CHILD_
#include "probe.cpp"
#endif

class probeB : public probe {
public:
  int mTypeCounter;
  probeB() : probe(257, 'B'), mTypeCounter(200000){ probe::sendIDMsg('B'); }
  void initialize();
};

void probeB::initialize(){
  while(true){ // Exited by force_patch
    sendMsg(mTypeCounter, false);
    mTypeCounter++;
  }
}
