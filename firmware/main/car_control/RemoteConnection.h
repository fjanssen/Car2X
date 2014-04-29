#ifndef REMOTECONNECTION_H_
#define REMOTECONNECTION_H_

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>

#include <stdio.h>
#include <alt_types.h>
#include "..\networking\CarProtocol.h"



#define TELNETPORT 23
#define MOTOR_IP_ADDRESSES "192.168.0.11", "192.168.0.12", "192.168.0.13", "192.168.0.14"



int initRemoteConnection();

int openConnections();

int closeConnections();

int sendData(char *pDatas, alt_u32 *iLengths);

int receiveDataSingleSocket(char *pData, alt_u32 *iLength, int iSocketNum);
int receiveData(char *pDatas, alt_u32 *iLengths);
int receiveDataExactCount(char *pDatas, alt_u32 *iLengths);

CCarProtocol* receiveNextPacket();
void receiveNextPackets(CCarProtocol** pProtocols);

#endif // REMOTECONNECTION_H_