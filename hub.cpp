#include "hub.h"

hub::hub(){
  size = sizeof(msgBuf) - sizeof(long);
  msgCount = 0;
  num_Active_Probes = 3;

  hPID = getpid();

  key = ftok(".",'o');
  msqID = msgget(key, IPC_EXCL|IPC_CREAT|0600);
  idProbes();
  start_time = std::chrono::high_resolution_clock::now();
}

// Associates each probe with a corresponding PID
void hub::idProbes(){
  IDbuffer idMsg;
  int ID_MSG_SIZE = sizeof(IDbuffer) - sizeof(long);

  msgrcv(msqID, (struct msgbuf *)&idMsg, ID_MSG_SIZE, 5555550, 0);
  aPID = idMsg.PID;
  msgrcv(msqID, (struct msgbuf *)&idMsg, ID_MSG_SIZE, 5555551, 0);
  bPID = idMsg.PID;
  msgrcv(msqID, (struct msgbuf *)&idMsg, ID_MSG_SIZE, 5555552, 0);
  cPID = idMsg.PID;


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
  char probeLetter;
  int msgType = 6666666; // Gets the first msg in queue that isn't an acknowledgement msg
  msgrcv(msqID, (struct msgbuf *)&msg, size, msgType, MSG_EXCEPT);

  if(msg.mtype == 8888888){ // ProbeC has exited
    std::cout << "-------------------------------------------------------------PROBE C TERMINATED\n";
    num_Active_Probes--;
    return;
  }

  else if(msg.PID == aPID) {
    probeLetter = 'A';
    if(msg.mtype == 7777777){ // ProbeA has exited
      std::cout << "-------------------------------------------------------------PROBE A TERMINATED\n";
      num_Active_Probes--;
      return;
    }
    else{ sendReturnMsg(); }
  }

  else if (msg.PID == bPID) { probeLetter = 'B'; }
  else { probeLetter = 'C'; }

  std::cout << "Hub(PID " << hPID << ") rcv from Probe" << probeLetter << "(PID " << msg.PID
  << ") with mtype " << msg.mtype << ": " << msg.msg << " (" << getTime() << "ns)\n";
}


// Used to send an acknowledgement msg to probeA
void hub::sendReturnMsg(){
  msgBuf.mtype = 6666666;
  msgBuf.msg = -1;
  msgBuf.PID = hPID;
  msgsnd(msqID, (struct msgbuf *)&msgBuf, size, 0);

  std::cout << "Hub(PID " << hPID << ") returnMsg sent to probeA with mtype " << msgBuf.mtype << ": "
  << msgBuf.msg << " (" << getTime() << "ns)\n\n";
}


void hub::deleteQ(){
  msgctl(msqID, IPC_RMID, NULL);
  std::cout << "\nQueue deleted via hub . . ." << std::endl;
}


// Final function that is called at termination
void hub::performExit(){
  std::cout << "\nAll probes have terminated, terminating DataHub\n";
  std::cout << "Total number of messages recieved: " << msgCount << "\n";
  deleteQ();
}


void hub::initialize(){
  while(num_Active_Probes > 0){
    rcvMsg();
    if(msgCount == 10000){ // Checks B exit condition
      std::cout << "-------------------------------------------------------------PROBE B TERMINATED\n";
      force_patch(bPID);
      num_Active_Probes--;
    }
    msgCount++;
  }
  performExit();
}


int main(){
  hub h;
  h.initialize();
}
