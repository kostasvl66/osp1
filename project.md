System launch: ./start -p <Probability-value> -n <attempts>

CLI launch: ./proc 1 ./proc 2 --- AFTER ./start

### Processes:

- Notes:

  - Message sending and receiving operations must be used in parallel.

  - A "TERM" message terminates all processes. "TERM", "ACK" and "NACK" messages are not affected by CHAN(?).

  - Connections between processes must be implemented using shared memory(in/out structures), while also using semaphores for synchronisation.

- Global Items:

  - p: Probability-value used for encoding/decoding every character in a message, by ENC1/2.

  - N: Number of times a message is allowed to fail being sent from P1/2 to P2/1.

  - Named Semaphores:
    - Full: Specifies if the message buffer is full(message has not been read)
    - Empty: Specifies if the message buffer is empty(message has been read)
  - Access Mutex: Makes sure only one process can access a given semaphore at a time

- P1/P2: Multi-User(Process) Input/Output

  - Receives input message through a command line interface.
  - Input message is sent to ENC1/2 for hashing.

  - Receives output message from ENC1/2, prints it in cli.

- ENC1/ENC2: Message Hasher for each respective proccess

  - Receives message from P1/2, maybe through shared memory.
  - Processes the message with a hash-function, the resulting hash is added at the end of the message, and used as a checksum.
  - If ACK has been received, sends encoded message to CHAN.
  - If NACK has been received, resends previously encoded message to CHAN, up to N times. If NACK continues being received more than N times, user is notified of failure sending the message.

  - Receives message from CHAN, decodes it using the given p value, processes and checks the checksum.
  - If checksum is correct, an ACK is sent to Sender, the checksum segment is removed and the message is sent to P1/2.
  - If cheksum is incorrect, a NACK is sent to Sender.

- CHAN: Communication/Encoding channel between Hashers

  - Receives message from ENC1/2.
  - Changes all message characters(including the checksum) using the given probability value "p".
  - Sends finalized(encoded) message to ENC1/2.
