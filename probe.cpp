#include "probe.h"

void probe::linkToQ(){
  size = sizeof(msgBuf) - sizeof(long);
  key_t key = ftok(".",'o');
  msqID = msgget(key, 0);
}

probe::probe(int seedValue): seed(seedValue), exitProbe(false){
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
void probe::rcvMsg(int msgType = 99999){
  msgbuffer msg;
  msgrcv(msqID, (struct msgbuf *)&msg, size, msgType, 0);

  std::cout << "Probe(PID " << PID << ") rcv from (PID " << msg.PID << ") with mtype "
  << msg.mtype << ": " << msg.msg << " (" << getTime() << "ns)\n\n";
}


// Generates and sends a message to q with the given mtype
// If sending from Prbe A, retrieves acknowledgement message
void probe::sendMsg(int msgType, bool fromA){
  generateReading(fromA);
  if(!exitProbe){
    msgBuf.mtype = msgType;
    msgBuf.PID = this->PID;
    msgsnd(msqID, (struct msgbuf *)&msgBuf, size, 0);


    std::cout << "Probe(PID " << this->PID << ") snd to hub with mtype " << msgBuf.mtype << ": " << msgBuf.msg
    << " (" << getTime() << "ns)" << std::endl;

    if(fromA){rcvMsg();}
  }
}


void probe::sendIDMsg(char probe){
  IDbuffer probeIDMsg;
  int ID_MSG_SIZE = sizeof(IDbuffer) - sizeof(long);

  switch(probe){
    case 'A':
      probeIDMsg.mtype = 22220;
      break;
    case 'B':
      probeIDMsg.mtype = 22221;
      break;
    case 'C':
      probeIDMsg.mtype = 22222;
      break;
  }
  probeIDMsg.PID = this->PID;
  msgsnd(msqID, (struct IDbuffer *)&probeIDMsg, ID_MSG_SIZE, 0);
}

void probe::displayExit(char probe){
  switch(probe){
    case 'A':
      std::cout << "A value smaller than 50 was produced" << std::endl;
      break;
    case 'B':
      std::cout << "The DataHub has received 10,000 messages, initiating force_patch" << std::endl;
    case 'C':
      std::cout << "Initiating kill_patch" << std::endl;
  }

  std::cout << "Probe " << probe << " was terminated . . ." << std::endl;
}


// Deletes the queue, used when probe is last to read a msg
void probe::deleteQ(char probeName){
  msgctl(msqID, IPC_RMID, NULL);
  std::cout << "Queue deleted via probe " << probeName << ". . ." << std::endl;
}
