#include "network.h"

void sendPacket (int socket, byte *buffer){

        int writtenBytes = 0, writeOffset = 0;
        while (writeOffset < MessageSize)
        {
            if ((writtenBytes = send(socket, buffer + writeOffset, MessageSize - writeOffset, 0)) > 0)

                writeOffset += writtenBytes;

            else
            {
                std::cerr << "Error writing.." << std::endl;
                std::cout << "Written bytes: " << writtenBytes << std::endl;
                std::cout << "Write offset: " << writeOffset << std::endl;
                printError(errno);
                exit(0);
            }
        }
}
void receivePacket (int socket, byte *buffer){

        int readBytes = 0, readOffset = 0;
        while (readOffset < MessageSize)
        {
            if (( readBytes = recv(socket, buffer + readOffset, MessageSize - readOffset, 0)) > 0)
            
                readOffset += readBytes;
            
            else
            {

                std::cerr << "Error reading.." << std::endl;
                std::cout << "Read bytes: " << readBytes << std::endl;
                std::cout << "Read offset: " << readOffset << std::endl;
                printError(errno);
                exit(0);
            }
        }
}