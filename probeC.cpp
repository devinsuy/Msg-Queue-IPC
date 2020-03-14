#ifndef _PROBE_C_
#define _PROBE_C_
#include "probe.cpp"

class probeC : public probe {
public:
  probeC() : probe(257){probe::sendIDMsg('C');}
  void deleteQ(){ probe::deleteQ('C'); }
};
#endif

int main(){
  probeC c;


}
