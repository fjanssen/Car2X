/*
 * socketserver.h
 *
 *  Created on: Jun 19, 2014
 *      Author: bergmann
 */

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

/*
 *    SSSSimpleSocketServerTask() - Manages the socket server connection and
 * calls relevant subroutines to manage the socket connection.
 */
void SSSSimpleSocketServerTask();

/*
 *  Task Priorities:
 *
 *  MicroC/OS-II only allows one task (thread) per priority number.
 */
#define SSS_SIMPLE_SOCKET_SERVER_TASK_PRIORITY  10
#define SSS_INITIAL_TASK_PRIORITY               5

/*
 * The IP, gateway, and subnet mask address below are used as a last resort
 * if no network settings can be found, and DHCP (if enabled) fails. You can
 * edit these as a quick-and-dirty way of changing network settings if desired.
 *
 * Default IP addresses are set to all zeros so that DHCP server packets will
 * penetrate secure routers. They are NOT intended to be valid static IPs,
 * these values are only a valid default on networks with DHCP server.
 *
 * If DHCP will not be used, select valid static IP addresses here, for example:
 *           IP: 192.168.1.234
 *      Gateway: 192.168.1.1
 *  Subnet Mask: 255.255.255.0
 */
#define IPADDR0   10
#define IPADDR1   10
#define IPADDR2   100
#define IPADDR3   105

#define GWADDR0   0
#define GWADDR1   0
#define GWADDR2   0
#define GWADDR3   0

#define MSKADDR0  255
#define MSKADDR1  255
#define MSKADDR2  255
#define MSKADDR3  0


/*
 * IP Port(s) for our application(s)
 */
#define SSS_PORT 23

/* Definition of Task Stack size for tasks not using Nichestack */
#define   TASK_STACKSIZE       2048

/*
 * TX & RX buffer sizes for all socket sends & receives in our sss app
 */
#define SSS_RX_BUF_SIZE  8192
#define SSS_TX_BUF_SIZE  8192

/*
 * Here we structure to manage sss communication for a single connection
 */
typedef struct SSS_SOCKET
{
  enum { READY, COMPLETE, CLOSE } state;
  int       fd;
  int       close;
  
  enum {UNKNOWN,WHEEL_LF,WHEEL_LB,WHEEL_RF,WHEEL_RB,ULTRASOUND,CAMERA,WIPORT} client_type;
  
  INT8U     rx_buffer[SSS_RX_BUF_SIZE];
  INT8U     *rx_wr_pos; // position we've written up to
} SSSConn;

typedef struct currEmReqAnswer{
	int stateVersion;
	int fd;
};

typedef struct currRemCtrlAnswer{
	int stateVersion;
	alt_u8 ip1;
	alt_u8 ip2;
	alt_u8 ip3;
	alt_u8 ip4;
	int fd;
};

typedef struct currCCtrlAnswer{
	int stateVersion;
	int v1;
	int v2;
	int v3;
	int v4;
	int fd;
};

#endif /* SOCKETSERVER_H_ */


