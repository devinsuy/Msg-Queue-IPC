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

