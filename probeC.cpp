#ifndef _PROBE_CHILD_
#define _PROBE_CHILD_
#include "probe.cpp"
#endif

class probeC : public probe {
public:
  int mTypeCounter;
  probeB() : probe(251, 'C'), mTypeCounter(30000){ probe::sendIDMsg('C'); }
  void deleteQ(){probe::deleteQ('C'); }
  void initialize();
};

// void probeB::initialize(){
//   while(!this->exitProbe){
//     sendMsg(mTypeCounter, false);
//     mTypeCounter++;
//   }
//   displayExit('C');
// }
