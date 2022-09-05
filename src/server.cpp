#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <sys/time.h>

#include "network.cpp"
#include "benchmark.cpp"

void benchmarkThroughput(int);

int main()
{

    sockaddr_in serverAddress;
    bzero((char *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0)
    {
        std::cerr << "Error establishing the server socket" << std::endl;
        printError(errno);
        exit(0);
    }

    int bindStatus = bind(serverSd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (bindStatus < 0)
    {
        std::cerr << "Error binding socket to local address" << std::endl;
        printError(errno);
        exit(0);
    }

    int ableToListen = listen(serverSd, 5);
    if (ableToListen < 0)
    {
        std::cerr << "Error listening" << std::endl;
        printError(errno);
        exit(0);
    }

    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    int clientSocket = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if (clientSocket < 0)
    {
        std::cerr << "Error accepting request from client!" << std::endl;
        printError(errno);
        exit(1);
    }

    benchmarkThroughput(clientSocket);

    close(clientSocket);
    close(serverSd);
    return 0;
}

void benchmarkThroughput(int socket)
{

    byte *buffer = new byte[MessageSize];
    memset(buffer, 0x41, MessageSize);

    int counter = 0;

    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
    do
    {
        receivePacket(socket, buffer);
        counter++;
    } while (counter < NbMessages);
    gettimeofday(&endTime, NULL);
    
    calculateThroughput(startTime, endTime);
}