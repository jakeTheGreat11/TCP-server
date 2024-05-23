#include <iostream>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main() {
    // Initialize winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return 1;
    }

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) {
        cerr << "Can't create a socket, Quitting" << endl;
        WSACleanup();
        return 1;
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
        cerr << "Can't bind socket, Quitting" << endl;
        closesocket(listening);
        WSACleanup();
        return 1;
    }

    // Tell Winsock the socket is for listening
    if (listen(listening, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Can't listen on socket, Quitting" << endl;
        closesocket(listening);
        WSACleanup();
        return 1;
    }

    // Wait for connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Can't create a client socket, Quitting" << endl;
        closesocket(listening);
        WSACleanup();
        return 1;
    }

    char host[NI_MAXHOST];      // Client remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connected on

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        cout << host << " connected on port " << service << endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }

    // Close listening socket
    closesocket(listening);

    // While loop : accept and echo message back to client
    char buf[4096];

    while (true) {
        ZeroMemory(buf, 4096);
        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            cerr << "Error in recv(), Quitting" << endl;
            break;
        }
        if (bytesReceived == 0) {
            cout << "Client disconnected" << endl;
            break;
        }
        // Echo message back to the client
        send(clientSocket, buf, bytesReceived, 0);
    }

    // Close socket
    closesocket(clientSocket);

    // Shutdown winsock
    WSACleanup();
    return 0;
}

