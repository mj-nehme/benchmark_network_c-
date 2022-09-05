#include <iostream>
#include <arpa/inet.h>
#include <sys/time.h>
#include <thread>
#include <unistd.h>
#include <netdb.h>

#include "network.cpp"
#include "benchmark.cpp"

void benchmarkThroughput(int);

int main()
{

    struct hostent *host = gethostbyname(serverIP);
    sockaddr_in sendSockAddr;
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int connected = connect(serverSocket, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
    if (connected < 0)
    {
        std::cerr << "Error connecting to socket.." << std::endl;
        printError(errno);
        exit(0);
    }
    benchmarkThroughput(serverSocket);
    close(serverSocket);
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
        sendPacket(socket, buffer);
        counter++;
    } while (counter < NbMessages);
    gettimeofday(&endTime, NULL);
    
    calculateThroughput(startTime, endTime);
}