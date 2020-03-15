#ifndef _PROBE_MANAGER_
#define _PROBE_MANAGER_
#include "probeA.cpp"
#include "probeB.cpp"
#endif

int main(){
  pid_t pid = fork();

//FIXME, need to look into using fork() on parent a 2nd time to
// run three concurrent processes, also probeC to be implemented

  if(pid > 0){ // Parent process
    probeA a;
    a.initialize();
  }
  else if(pid == 0){ // Child process
    probeB b;
    b.initialize();
  }
  else{
    perror("Fork Error");
  }

}
