## What is JabberHive?
JabberHive is a modular ChatBot system. All "modules" are in fact separate
programs linked together using the JabberHive Protocol. Please refer to the
protocol for more information.

## Component Description
* CLI Gateway for a JabberHive network.
* Allows the use of the Command Line Interface to send requests using stdin.
* All replies are displayed in stdout.
* Handles the lack of pipelining by not reading from stdin if it's not ready to
send.

## JabberHive Protocol Compatibility
* **Protocol Version(s):** 1.
* **Inbound Connections:** None.
* **Outbound Connections:** Single.
* **Pipelining:** No.
* **Behavior:** Gateway.

## Dependencies
- POSIX compliant OS.
- C compiler (with C99 support).
- (GNU) make.

## How to Build
* Download the source code.
* Enter the following command: ``$ make``.
* Run ``$ ./jh-cli`` to see how to use the binary.

## Examples of Use
* Debug a JabberHive network by connecting to the socket ``/tmp/jh0``:
   ``$ ./jh-cli /tmp/jh0``, then ``?RR what's up, doc?``.
* Teach a JabberHive network the content of some file through the socket
   ``/tmp/jh0``: each line of the file should start by ``?RL ``, then it is
   simply a case of ``$ cat file | ./jh-cli /tmp/jh0``. Cutting files so that
   this can be run in parallel is recommended.
