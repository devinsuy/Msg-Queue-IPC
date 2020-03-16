#include "probe.h"

void probe::linkToQ(){
  size = sizeof(msgBuf) - sizeof(long);
  key_t key = ftok(".",'o');
  msqID = msgget(key, 0);
}


probe::probe(int seedValue, char probeLetter): seed(seedValue), letter(probeLetter), exitProbe(false){
    linkToQ();
    this->PID = getpid();
    start_time = std::chrono::high_resolution_clock::now();
  }


// Returns the current time in nanoseconds
long probe::getTime(){
  t = std::chrono::high_resolution_clock::now();
  auto t_duration = std::chrono::duration_cast
  <std::chrono::duration<double>>(t-start_time);

  return t_duration.count() *1000000000;
}


// Generates a random value divisible by the probe's seed value
void probe::generateReading(bool checkReading){
  int randomInt = 0;
  while((!(randomInt % this->seed == 0)) || randomInt == 0){
    randomInt = rand();
    if(checkReading && randomInt < 50){
      exitProbe = true;
      break;
    }
  }
  msgBuf.msg = randomInt;
}


// Retrieves a msg from q with given mtype will
// retrieve acknowledgement msg from hub by default
void probe::rcvMsg(int msgType = 6666666){
  msgbuffer msg;
  msgrcv(msqID, (struct msgbuf *)&msg, size, msgType, 0);

  std::cout << "Probe" << letter << "(PID " << PID << ") rcv from Hub(PID " << msg.PID << ") with mtype "
  << msg.mtype << ": " << msg.msg << " (" << getTime() << "ns)\n\n";
}


// Generates and sends a message to q with the given mtype
// If sending from Probe A, retrieves acknowledgement message
void probe::sendMsg(int msgType, bool fromA){
  generateReading(fromA);
  if(!exitProbe){
    msgBuf.mtype = msgType;
    msgBuf.PID = this->PID;
    msgsnd(msqID, (struct msgbuf *)&msgBuf, size, 0);

    std::cout << "Probe" << letter << "(PID " << this->PID << ") snd to hub with mtype " << msgBuf.mtype << ": " << msgBuf.msg
    << " (" << getTime() << "ns)" << std::endl;

    if(fromA){rcvMsg();}
  }
}


// Used to send a signal message to the Hub
//  see README.txt for MType Codes
void probe::sendSignalMsg(int msgType){
  msgBuf.msg = -1;
  msgBuf.mtype = msgType;
  msgBuf.PID = this->PID;
  msgsnd(msqID, (struct msgbuf *)&msgBuf, size, 0);
}


// Associates each probe with its PID at initialization
void probe::sendIDMsg(char probe){
  IDbuffer probeIDMsg;
  int ID_MSG_SIZE = sizeof(IDbuffer) - sizeof(long);

  switch(probe){
    case 'A':
      probeIDMsg.mtype = 5555550;
      break;
    case 'B':
      probeIDMsg.mtype = 5555551;
      break;
    case 'C':
      probeIDMsg.mtype = 5555552;
      break;
  }
  probeIDMsg.PID = this->PID;
  msgsnd(msqID, (struct IDbuffer *)&probeIDMsg, ID_MSG_SIZE, 0);
}
