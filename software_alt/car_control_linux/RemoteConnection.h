#ifndef REMOTECONNECTION_H_
#define REMOTECONNECTION_H_


#include <alt_types.h>
#include "../networking/CarProtocol.h"



#define TELNETPORT 23
#define MOTOR_IP_ADDRESSES "192.168.0.11", "192.168.0.12", "192.168.0.13", "192.168.0.14"


/*
 * Initalizes the sockets. 
 * Returns always 0.
 */
int initRemoteConnection();

/*
 * Binds the sockets to the addresses given in the constant MOTOR_IP_ADDRESSES.
 * Returns a value < 0 if one of the sockets could not be connected.
 */
int openConnections();

/*
 * Tries to close all four sockets wether they were open or not.
 * Returns always 0.
 */
int closeConnections();

/*
 * Sens the given data of the given lengths to the corresponding motor-ECUs.
 * The pDatas must be of the following structure:
 * Bytes 0   to iLength[0]-1 are send to motor 1
 * Bytes 128 to iLength[1]-1 are send to motor 2
 * Bytes 256 to iLength[2]-1 are send to motor 3
 * Bytes 384 to iLength[3]-1 are send to motor 4.
 *
 * The total length of pDatas must be 4*128. The max. value in iLengths must be 128.
 *
 * The send process will be as short as possible. So there is only a minimum difference between
 * the data delivery times.
 *
 * Returns 0 if every thing was successful send otherwise the return value gives the count of fails.
 */
int sendData(char *pDatas, alt_u32 *iLengths);

/*
 * Various receive functions to cover differnt timing constrains.
 * The pData and iLengths inputs are as the ones mentioned in sendData(..).
 * 
 * receiveDataSingleSocket will only receive from the given socket index (starting with 0).
 *
 * receiveData will receive from all sockets.
 * receiveDataExactCount does the same but blocks until the given iLengths are exactly reached.
 *
 * The exact count of received bytes is stored in the iLengths input.
 * Returns 0 if every thing was successful send otherwise the return value gives the count of fails.
 */
int receiveDataSingleSocket(char *pData, alt_u32 *iLength, int iSocketNum);
int receiveData(char *pDatas, alt_u32 *iLengths);
int receiveDataExactCount(char *pDatas, alt_u32 *iLengths);

/*
 * Blocks until a CarProtocol packet can be received from the given socket index (starting with 0).
 * The received packet is the return value.
 */ 
CCarProtocol* receiveNextPacket(int iSocketNum);

/*
 * Calls receiveNextPacket for all sockets and stores the returned references to the given array.
 */ 
void receiveNextPackets(CCarProtocol** pProtocols);

#endif // REMOTECONNECTION_H_
