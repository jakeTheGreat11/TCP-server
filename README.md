# TCP Server

This is a simple TCP server written in C++ that listens for incoming connections, accepts clients, and echoes back any messages received from the clients.

## Prerequisites

Before running the server, ensure that you have the following:

- Windows operating system
- C++ compiler with support for Winsock (e.g., MinGW, Visual Studio)
- Basic understanding of TCP/IP networking

## How to Use

1. **Compile the Code**: Compile the code using your preferred C++ compiler. Make sure to link against the Winsock library (`ws2_32.lib`).

   Example with MinGW:
   ```
   g++ server.cpp -o server.exe -lws2_32
   ```

2. **Run the Server**: Execute the compiled executable to start the server.

   ```
   ./server.exe
   ```

3. **Connect Clients**: Clients can connect to the server using a TCP/IP client program (e.g., Telnet, PuTTY).

4. **Interact with Clients**: Once a client is connected, the server will echo back any messages received from the client.

5. **Terminate the Server**: To terminate the server, press `Ctrl + C` or close the terminal window.

## Important Notes

- This server listens on port `54000` by default. You can change the port by modifying the `hint.sin_port` value in the code.
- Ensure that the Winsock library is correctly linked during compilation to avoid linker errors.
