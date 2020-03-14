#ifndef _PROBE_CHILD_
#define _PROBE_CHILD_
#include "probe.cpp"
#endif

class probeB : public probe {
public:
  int mTypeCounter;
  probeB() : probe(257), mTypeCounter(10000){std::cout << "B initialized with PID " << this->PID; probe::sendIDMsg('B'); }
  void deleteQ(){probe::deleteQ('B'); }
  void initialize();
};

void probeB::initialize(){
  while(!this->exitProbe){
    sendMsg(mTypeCounter, false);
    mTypeCounter++;
  }
  displayExit('B');
}
