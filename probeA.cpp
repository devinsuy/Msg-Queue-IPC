#ifndef _PROBE_CHILD_
#define _PROBE_CHILD_
#include "probe.cpp"
#endif

class probeA : public probe {
public:
  int mTypeCounter;
  probeA() : probe(997, 'A'), mTypeCounter(1){ probe::sendIDMsg('A'); }
  void deleteQ(){probe::deleteQ('A');}
  void initialize();
};

void probeA::initialize(){
  while(!this->exitProbe){
    sendMsg(mTypeCounter, true);
    mTypeCounter++;
  }
  sendSignalMsg(77777);
  displayExit('A');
};
