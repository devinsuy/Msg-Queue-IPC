#ifndef _PROBE_CHILD_
#define _PROBE_CHILD_
#include "probe.cpp"
#endif

class probeA : public probe {
public:
  int mTypeCounter;
  probeA() : probe(997), mTypeCounter(1){std::cout << "A initialized with PID " << this->PID; probe::sendIDMsg('A'); }
  void deleteQ(){probe::deleteQ('A');}
  void initialize();
};

void probeA::initialize(){
  while(!this->exitProbe){
    sendMsg(mTypeCounter, true);
    mTypeCounter++;
  }
  displayExit('A');
};
