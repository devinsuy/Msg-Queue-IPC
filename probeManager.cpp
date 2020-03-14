#ifndef _PROBE_MANAGER_
#define _PROBE_MANAGER_
#include "probeA.cpp"
#include "probeB.cpp"
#endif

int main(){

  //probeA a;
  probeB b;
  b.initialize();
  //a.initialize();

  // pid_t pid = fork();
  //
  // if(pid > 0){ // Parent process
  //   probeA a;
  //   a.initialize();
  // }
  // else if(pid == 0){ // Child process
  //   //probeB b;
  //   //b.initialize();
  // }
  // else{
  //   perror("Fork Error");
  // }

}
