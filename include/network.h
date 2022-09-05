#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "config.h"
#endif

#ifndef __ERRORS_H__
#define __ERRORS_H__
#include "errors.h"
#endif

void sendPacket (int socket, byte *buffer);
void receivePacket (int socket, byte *buffer);