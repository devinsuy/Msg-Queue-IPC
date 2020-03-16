#ifndef _PROBE_MANAGER_
#define _PROBE_MANAGER_
#include "probeA.cpp"
#include "probeB.cpp"
#include "probeC.cpp"
#endif

int main(){
  pid_t pid = fork();

  if(pid > 0){ // Probe A
    probeA a;
    a.initialize();
  }

  else if(pid == 0){
    pid = fork();

    if(pid > 0){ // Probe B
      probeB b;
      b.initialize();
    }
    else if(pid == 0){ // Probe C
      probeC c;
      c.initialize();
    }
    else{ perror("Error forking process\n"); }
  }

  else{ perror("Error forking process"); }
}
