#include <errno.h>
#include <cstring>
#include <iostream>

void printError(int errnb)
{

    if (errnb != 0)
    {
        char buffer[256];
        char *errorMsg = strerror_r(errnb, buffer, 256); // GNU-specific version, Linux default
        std::cout << "Error: " << errorMsg << std::endl; //return value has to be used since buffer might not be modified
    }
}