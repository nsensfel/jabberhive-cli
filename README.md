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
- CMake.
