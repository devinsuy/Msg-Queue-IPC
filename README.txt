v1.2, 03/14/20

Compile:
    1. Open terminal -> cd to IPC folder
    2. Enter "bash 1_runHub.sh" in one window
    3. Enter "bash 2_runProbes.sh" in the other window

v1.1: Sets up IPC between Probes A&B with the DataHub
v1.2: Fixed abnormal termination, A and B are now stable
TODO v1.3: Implement probeC


////////////////////////////////////////////////////////////////////
[MType Codes]
  (1 : ...)      = Range of probeA messages
  (20,000 : ...) = Range of probeB messages
  (30,000 : ...) = Range of probeC messages

[Signal MTypes] msg is set to -1
  77,777 = terminating message (probeA -> Hub)
  88,888 = terminating message (ProbeC -> Hub)
  99,999 = acknowledgment message (Hub -> ProbeA)
