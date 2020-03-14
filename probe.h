#ifndef _PROBE_
#define _PROBE_
#include "msgbuffer.h"
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <chrono>
#include <stdio.h>
#include <iostream>


class probe {
protected: // We don't ever want to instantiate probe class
  probe(int seedValue);

  bool exitProbe;
  int PID;
  int key;
  int seed;
  int msqID;
  int size;
  msgbuffer msgBuf;
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point t;

  void linkToQ();
  void sendIDMsg(char);
  void sendMsg(int, bool);
  void rcvMsg(int);
  void generateReading(bool);
  void deleteQ(char);
  void exit();
  void displayExit(char);
  long getTime();

};
#endif
