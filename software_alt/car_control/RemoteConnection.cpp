#include "RemoteConnection.h"

char *cIPAddresses[4] = {MOTOR_IP_ADDRESSES};
SOCKET sSockets[4];
SOCKADDR_IN sAddresses[4];
bool bConnected[4];


int initRemoteConnection()
{
	WSADATA wsa;
	int failCode = 0;
	
	failCode = WSAStartup(MAKEWORD(2,0), &wsa);
	if(failCode != 0)
	{
		printf("Failure: startWinsock, fail-code: %d\n", failCode);
		return 1;
	}
	printf("WinSock started\n");

	for(int i = 0; i < 4; i++)
	{
		sSockets[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(sSockets[i] == INVALID_SOCKET)
			printf("Failure: socket number %d could not be generated\n", i);
		else
			printf("Socket number %d generated\n", i);
		bConnected[i] = false;
	}



	return 0;
}

int openConnections()
{
	int failCode = 0;

	memset(&sAddresses,0,4*sizeof(SOCKADDR_IN)); 

	for(int i = 0; i < 4; i++)
	{
		if(sSockets[i] == INVALID_SOCKET)
			continue;

		sAddresses[i].sin_family		= AF_INET;
		sAddresses[i].sin_port			= htons(TELNETPORT); 
		sAddresses[i].sin_addr.s_addr	= inet_addr(cIPAddresses[i]); 

		failCode = connect(sSockets[i],(SOCKADDR*)&sAddresses[i],sizeof(SOCKADDR));

		if(failCode == SOCKET_ERROR)
			printf("Failure: can not connect socket %d, fail-code: %d\n", i, WSAGetLastError());
		else
		{
			printf("socket %d is connected to %s\n", i, cIPAddresses[i]);
			bConnected[i] = true;
		}
	}

	

	return 0;
}

int closeConnections()
{
	// cleanup
	for(int i = 0; i < 4; i++)
	{
		closesocket(sSockets[i]);
	}
    WSACleanup();
	return 0;
}

int sendData(char *pDatas, alt_u32 *iLengths)
{
	int fail = 0;

	for(int i = 0; i < 4; i++)
	{
		if(!bConnected[i])
			continue;

		if(iLengths[i] != send(sSockets[i], pDatas+i*128, iLengths[i], 0))
			fail++;
	}
	//printf("Gesendet...\n");
	return fail;
}

int receiveDataSingleSocket(char *pData, alt_u32 *iLength, int iSocketNum)
{
	if(!bConnected[iSocketNum])
		return 0;

	*iLength = recv(sSockets[iSocketNum], pData, *iLength, 0);

	return *iLength;
}

int receiveData(char *pDatas, alt_u32 *iLengths)
{
	int fail = 0;

	for(int i = 0; i < 4; i++)
	{
		if(!bConnected[i])
			continue;

		iLengths[i] = recv(sSockets[i], pDatas+i*128, 128, 0);
		if(iLengths[i] < 0)
			fail++;
	}

	return fail;
}

int receiveDataExactCount(char *pDatas, alt_u32 *iLengths)
{
	bool finished = true;
	int fail = 0;
	int counts[4];

	counts[0] = counts[1] = counts[2] = counts[3] = 0;

	do
	{
		finished = true;

		for(int i = 0; i < 4; i++)
		{
			if(!bConnected[i])
			{
				finished &= true;
				iLengths[i] = 0;
				continue;
			}

			counts[i] += recv(sSockets[i], pDatas+i*128+counts[i], iLengths[i]-counts[i], 0);
			if(counts[i] < 0)
			{
				counts[i] = 0;
				fail++;
			}
			else if(counts[i] == iLengths[i])
				finished &= true;
			else
				finished &= false;
		}
	}while(!finished);
	

	return fail;
}



CCarProtocol* receiveNextPacket(int iSocketNum)
{
	char cBuffer[256];
	int iLength = 0;
	int iIdx = 0;
	int iStartIdx = -1;
	int iPayloadLength = 0;

	if(!bConnected[iSocketNum])
		return 0;

	while(iStartIdx < 0)
	{
		iLength += recv(sSockets[iSocketNum], cBuffer + iLength, 128 - iLength, 0);	

		for(; iIdx < iLength-3; iIdx++)
		{
			if(cBuffer[iIdx] == 'C' && cBuffer[iIdx+1] == 'A' && cBuffer[iIdx+2] == 'R' && cBuffer[iIdx+3] == 'P')
			{
				iStartIdx = iIdx;
				break;
			}
		}
	}
	iIdx += 4;

	// Is the Header not complete?
	while(iIdx+4 > iLength)
	{
		iLength += recv(sSockets[iSocketNum], cBuffer + iLength, iIdx+4 - iLength, 0);		
	}

	// How much Payload?
	iPayloadLength = cBuffer[iStartIdx+6] << 8;
	iPayloadLength += cBuffer[iStartIdx+7];

	iPayloadLength += 8;

	while(iStartIdx + iPayloadLength > iLength)
	{
		iLength += recv(sSockets[iSocketNum], cBuffer + iLength, iStartIdx + iPayloadLength - iLength, 0);		
	}

	return new CCarProtocol((alt_u8*) cBuffer+iStartIdx, iLength - iStartIdx);
}

void receiveNextPackets(CCarProtocol** pProtocols)
{
	for(int i = 0; i < 4; i++)
	{
		pProtocols[i] = receiveNextPacket(i);
	}
}