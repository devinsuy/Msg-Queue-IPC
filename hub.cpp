#include "hub.h"

hub::hub(){
  size = sizeof(msgBuf) - sizeof(long);

  key = ftok(".",'o');
  msqID = msgget(key, IPC_EXCL|IPC_CREAT|0600);

  msgCount = 0;
  hPID = getpid();
  idProbes();
  start_time = std::chrono::high_resolution_clock::now();
}


// Associates each probe with a corresponding PID
void hub::idProbes(){
  IDbuffer idMsg;
  int ID_MSG_SIZE = sizeof(IDbuffer) - sizeof(long);

  // msgrcv(msqID, (struct msgbuf *)&idMsg, ID_MSG_SIZE, 22220, 0);
  // aPID = idMsg.PID;
  msgrcv(msqID, (struct msgbuf *)&idMsg, ID_MSG_SIZE, 22221, 0);
  bPID = idMsg.PID;
  // msgrcv(msqID, (struct msgbuf *)&idMsg, ID_MSG_SIZE, 22222, 0);
  // cPID = idMsg.PID;


  std::cout << "Hub is ready to recieve messages from Probes:\n   A(PID " << aPID
  << "), B(PID " << bPID << "), C(PID " << cPID << ")\n";
}

// Returns the current time in nanoseconds
long hub::getTime(){
  t = std::chrono::high_resolution_clock::now();
  auto t_duration = std::chrono::duration_cast
  <std::chrono::duration<double>>(t-start_time);

  return t_duration.count() *1000000000;
}


// Retrieves a msg from q with given mtype, if retrieving
// a msg sent by probeA, sends an acknowledgement msg
void hub::rcvMsg(){
  msgbuffer msg;
  int msgType = 99999; // Gets the first msg in queue that isn't an acknowledgement msg
  msgrcv(msqID, (struct msgbuf *)&msg, size, msgType, MSG_EXCEPT);

  std::cout << "(!!" << msgCount << ") Hub(PID " << hPID << ") rcv from probe(PID " << msg.PID
  << ") with mtype " << msg.mtype << ": " << msg.msg << " (" << getTime() << "ns)\n";

  if(msg.PID == aPID){sendReturnMsg();}
}


// Used to send an acknowledgement msg to probeA
void hub::sendReturnMsg(){
  msgBuf.mtype = 99999;
  msgBuf.msg = -1;
  msgBuf.PID = hPID;
  msgsnd(msqID, (struct msgbuf *)&msgBuf, size, 0);

  std::cout << "Hub(PID " << hPID << ") returnMsg sent to probeA with mtype " << msgBuf.mtype << ": "
  << msgBuf.msg << " (" << getTime() << "ns)\n\n";
}


void hub::initialize(){
  while(msgCount < 30000){
    rcvMsg();
    if(msgCount = 10000){
      force_patch(bPID);
    }
    msgCount++;
  }
}

// Deletes the queue, used when hub is last to read a msg
void hub::deleteQ(){
  msgctl(msqID, IPC_RMID, NULL);
  std::cout << "Queue deleted via hub . . ." << std::endl;
}


int main(){
  hub h;
  h.initialize();
}
