Description: Implements inter-process communication between four concurrently executing
programs: ProbeA, ProbeB, ProbeC, and DataHub through the usage of a single message
queue with the fork(), msgget(), msgrcv(), msgsnd(), and msgctl() system calls.
Each probe continues to generate a random integer that is divisible by its corresponding
seed value to send as a “message” to the DataHub.
Probe A’s random integer messages are all divisible by 997, Probe B’s by 257, and Probe
C’s by 251. Each probe eventually terminates following it’s own exit condition. Probe A
terminates upon randomly generating a value less than 50, upon receiving a total of
10,000 message the Data Hub sends a signal to terminate Probe B, and Probe C is
terminated by a user kill command.
Probe A has special behavior in that it waits to receive an acknowledgement message
from the DataHub after each it sends before it continues to send more messages, in
which execution shifts to the other concurrently running probes.
The fork() system call is utilized within a ProbeManager to assign each of the three
probes a unique PID. Upon initialization each probe sends a single smaller message to
the DataHub which is utilized to associate each probe with its corresponding PID. This
PID is also utilized for specific behaviors such as determining whether or not to send an
acknowledgement message, reducing the size of the msgbuffer structure used in our
communication protocol.
As overall behavior is fairly similar between probes, a Probe superclass is defined to
avoid redundancy between Probes A, B and C which implement their differences in their
own respective classes.
Upon termination of all probes, the DataHub displays the total # of messages received
and the number of messages remaining in queue (0) before deleting it and terminating.
-----------------------------------------------------------------------------------------------------------------------------
v1.3, 03/15/20

Compile:
    1. Open terminal -> cd to IPC folder
    2. Enter "bash 1_runHub.sh" in one window
    3. Enter "bash 2_runProbes.sh" in the other window
    4. Terminate probeC with command kill -10 (PID HERE)

v1.1: Sets up IPC between Probes A&B with the DataHub
v1.2: Fixed abnormal termination, A and B are now stable
v1.3: Implemented probeC, updated MTypes to be larger as to not realistically be overlapped by the range of probeC messages.


////////////////////////////////////////////////////////////////////
[MType Codes]
  (1 : ...)      = Range of probeA messages
  (200,000 : ...) = Range of probeB messages
  (300,000 : ...) = Range of probeC messages


[ID MTypes] Uses IDbuffer and contains no msg, only used at initialization
  5,555,550 = Associates Probe's PID with A 
  5,555,551 = Associates Probe's PID with B 
  5,555,550 = Associates Probe's PID with C 


[Signal MTypes] msg is set to -1
  6,666,666 = acknowledgment message (Hub -> ProbeA)
  7,777,777 = signal termination of probeA (probeA -> Hub)
  8,888,888 = signal termination of probeC (ProbeC -> Hub)

