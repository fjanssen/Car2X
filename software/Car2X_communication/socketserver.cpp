
extern "C" {

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* MicroC/OS-II definitions */
#include "includes.h"

/* Simple Socket Server definitions */
#include "socketserver.h"
#include "alt_error_handler.h"

/* Nichestack definitions */
#include "ipport.h"
#include "tcpport.h"

//CarProtocol: Used to parse the received bytes from the TCP connection into a Message
#include "CarProtocol.h"
#include "CarMessage.h"

//use alt types
#include <alt_types.h>

} // extern C

//Message imports
#include "WelcomeMessage.h"
#include "MotorMeasurementMessage.h"
#include "MotorVelocityMessage.h"
#include "UltrasoundDistanceMessage.h"
#include "AccelerationValuesMessage.h"
#include "ADCInfoMessage.h"
#include "ADCValuesMessage.h"
//Car2X Message imports
#include "CEmergencyBrakeMessage.h"
#include "CControlMessage.h"
#include "CInfoStateMessage.h"
#include "CInfoSensorMessage.h"
#include "CRemoteControlMessage.h"
#include "CVelocityMessage.h"
//end of message includes

#define CAR_HEADER_LENGTH 8

/*
 * sss_reset_connection()
 *
 * This routine will, when called, reset our SSSConn struct's members
 * to a reliable initial state. Note that we set our socket (FD) number to
 * -1 to easily determine whether the connection is in a "reset, ready to go"
 * state.
 */
void sss_reset_connection(SSSConn* conn)
{
  memset(conn, 0, sizeof(SSSConn));

  conn->fd = -1;
  conn->state = SSS_SOCKET::READY;
  conn->rx_wr_pos = conn->rx_buffer;
  return;
}

/*
 * sss_handle_accept()
 *
 * This routine is called when ever our listening socket has an incoming
 * connection request. Since this example has only data transfer socket,
 * we just look at it to see whether its in use... if so, we accept the
 * connection request and call the telent_send_menu() routine to transmit
 * instructions to the user. Otherwise, the connection is already in use;
 * reject the incoming request by immediately closing the new socket.
 *
 * We'll also print out the client's IP address.
 */
void sss_handle_accept(int listen_socket, SSSConn* conn)
{
  int                 socket, len;
  struct sockaddr_in  incoming_addr;

  len = sizeof(incoming_addr);

  if ((conn)->fd == -1)
  {
     if((socket=accept(listen_socket,(struct sockaddr*)&incoming_addr,&len))<0)
     {
         alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE, (void *) "[sss_handle_accept] accept failed");
     }
     else
     {
        (conn)->fd = socket;
        //TODO: send welcome message
        printf("[sss_handle_accept] accepted connection request from %s\n",
               inet_ntoa(incoming_addr.sin_addr));
     }
  }
  else
  {
    printf("[sss_handle_accept] rejected connection request from %s\n",
           inet_ntoa(incoming_addr.sin_addr));
  }

  return;
}


/*
 * sss_exec_command()
 *
 * This routine is called whenever we have new, valid receive data from our
 * sss connection. It will parse through the data simply looking for valid
 * commands to the sss server.
 *
 * Incoming commands to talk to the board LEDs are handled by sending the
 * MicroC/OS-II SSSLedCommandQ a pointer to the value we received.
 *
 * If the user wishes to quit, we set the "close" member of our SSSConn
 * struct, which will be looked at back in sss_handle_receive() when it
 * comes time to see whether to close the connection or not.
 */
void sss_exec_command(CCarProtocol * receivedPacket)
{
   //TODO: read received data from connection struct and write to shared memory

	if(!receivedPacket->isValid())
	{
		printf("the received packet was not generated successfully and cant be handled by sss_exec_command!\n");
		return;
	}


	int iMessageCount = receivedPacket->getMessageCount();

	for(alt_u32 i = 0;i < iMessageCount;i++)
	{
		//handle each message separately
		CCarMessage *currentMessage = receivedPacket->getNthMessage(i);

		alt_u8 messageType = currentMessage->getType();

		switch(messageType){

		//WelcomeMessage
		case 0x01:
		{
			CWelcomeMessage *welcomeMessage = (CWelcomeMessage *) currentMessage;
			break;
		}
		// MotorVelocity
		case 0x04:
		{
			CMotorVelocityMessage *motorVelocityMessage = (CMotorVelocityMessage *) currentMessage;
			break;
		}
		// MotorMeasurement
		case 0x05:
		{
			CMotorMeasurementMessage *motorMeasurememtMessage = (CMotorMeasurementMessage *) currentMessage;
			break;
		}
		// Ultrasound-Sensor
		case 0x08:
		{
			CUltrasoundDistanceMessage *ultrasoundDistanceMessage = (CUltrasoundDistanceMessage *) currentMessage;
			break;
		}
		// Acceleration-Sensor
		case 0x09:
		{
			CAccelerationValuesMessage *accelerationValuesMessage = (CAccelerationValuesMessage* ) currentMessage;
			break;
		}
		//ADC-Sensor
		case 0x0A:
		{
			// If subtype is 0 then it's a InfoMessage otherwise a ValuesMessage
			if(currentMessage->getSubType() == 0)
					CADCInfoMessage 	*adcInfoMessage = (CADCInfoMessage *) currentMessage;
			else
					CADCValuesMessage 	*adcValuesMessage = (CADCValuesMessage *) currentMessage;
			break;
		}
		//TODO: Add the other message types too (Check CarProtocol.cpp)

		}
	}


}


/*
 * Try to receive bytes on the given connection
 * Additionally updates rx_wr_position in the connection data structure
 * Returns the number of bytes received
 */
int receive_bytes(SSSConn* conn){
	int rx_code = recv(conn->fd, (char *) conn->rx_wr_pos,
	        SSS_RX_BUF_SIZE - (conn->rx_wr_pos - conn->rx_buffer) -1, 0);

	if(rx_code > 0)
	{
	   conn->rx_wr_pos += rx_code;
	}

	return rx_code;
}



/*
 * sss_handle_receive()
 *
 * This routine is called whenever there is a sss connection established and
 * the socket assocaited with that connection has incoming data. We will first
 * look for a newline "\n" character to see if the user has entered something
 * and pressed 'return'. If there is no newline in the buffer, we'll attempt
 * to receive data from the listening socket until there is.
 *
 * The connection will remain open until the user enters "Q\n" or "q\n", as
 * deterimined by repeatedly calling recv(), and once a newline is found,
 * calling sss_exec_command(), which will determine whether the quit
 * command was received.
 *
 * Finally, each time we receive data we must manage our receive-side buffer.
 * New data is received from the sss socket onto the head of the buffer,
 * and popped off from the beginning of the buffer with the
 * sss_exec_command() routine. Aside from these, we must move incoming
 * (un-processed) data to buffer start as appropriate and keep track of
 * associated pointers.
 */
void sss_handle_receive(SSSConn* conn)
{
  int data_used = 0, rx_code = 0;
  int iBytesReceived = 0;
  conn->rx_wr_pos = conn->rx_buffer;

  printf("recvloop\n");
  conn->state = conn->close ? SSSConn::CLOSE : SSSConn::READY;

  //while(conn->state != SSSConn::CLOSE)
	  while(false)
  {
	  printf("%i\n",conn->close);
	 //start to receive a new CARP packet here
	  printf("recvzero\n");
	 while(iBytesReceived < 4 && !conn->close){
	 		 		iBytesReceived += receive_bytes(conn);
	 		 		if(iBytesReceived==0){
	 		 		conn->close=SSSConn::CLOSE;
	 		 		}
	 }

	 //as long as the first 4 bytes are not CARP
	 printf("notcarp\n");
	 while(!(conn->rx_buffer[0] == 'C' && conn->rx_buffer[1] == 'A' && conn->rx_buffer[2] == 'R' && conn->rx_buffer[3] == 'P')&& !conn->close){

		 iBytesReceived -= 1;
		 conn->rx_wr_pos -= 1;

		 //CARP HEADER NOT FOUND => THROW AWAY rx_buffer[0] and receive new 4th byte
		 memmove(conn->rx_buffer,conn->rx_buffer+1,iBytesReceived);

		 //clear off the last element that has been moved to the left
		 *(conn->rx_wr_pos) = 0;

		 //receive a new 4th byte if there are not enough bytes anymore
		 while(iBytesReceived < 4 && !conn->close){
		 		iBytesReceived += receive_bytes(conn);
		 }

	 }

	 //CARP header was received successfully, starting at conn->rx_buffer
	 //now wait for the full header (8 bytes) to arrive
	 printf("recvcarp\n");
	 while(iBytesReceived < 8 && !conn->close){
		 iBytesReceived += receive_bytes(conn);
	 }

	 //full header arrived, now parse payload length
	 int 	iPayloadLength  = conn->rx_buffer[6] << 8;
	      	iPayloadLength += conn->rx_buffer[7];

	 //received payload so far is everything except CAR_HEADER_LENGTH = 8 bytes
	 //wait for the whole payload to be received
	 printf("recvpayl\n");
	 while(iBytesReceived - CAR_HEADER_LENGTH < iPayloadLength&& !conn->close){
		 iBytesReceived += receive_bytes(conn);
	 }

	 //output
	 printf("msg: ");
	 for (int i = 0; i < iPayloadLength+CAR_HEADER_LENGTH; i++) {
		 printf("%02x ", conn->rx_buffer[i]&0xFF);
	 }
	 printf("\n");

	 //send dummy back
	 send(conn->fd,(char*)conn->rx_buffer,iPayloadLength+CAR_HEADER_LENGTH,0);


	 //parse the found CCarProtocol object
	 CCarProtocol * parsedPacket = new CCarProtocol((alt_u8 *)conn->rx_buffer,iPayloadLength+CAR_HEADER_LENGTH);

	 //clear the buffer: delete message from it:
	 memmove(conn->rx_buffer,conn->rx_buffer+iPayloadLength+8,iBytesReceived-iPayloadLength-CAR_HEADER_LENGTH);
	 conn->rx_wr_pos -= (iPayloadLength+CAR_HEADER_LENGTH);
	 memset(conn->rx_wr_pos,0,iPayloadLength+CAR_HEADER_LENGTH);

	 iBytesReceived -= (iPayloadLength+CAR_HEADER_LENGTH);

	 //execute whatever the message wants us to to
	 sss_exec_command(parsedPacket);

	 delete(parsedPacket);

    /*
     * When the quit command is received, update our connection state so that
     * we can exit the while() loop and close the connection
     */
    conn->state = conn->close ? SSSConn::CLOSE : SSSConn::READY;

  }

  printf("[sss_handle_receive] closing connection\n");
  close(conn->fd);
  sss_reset_connection(conn);

  return;
}

/*
 * SSSSimpleSocketServerTask()
 *
 * This MicroC/OS-II thread spins forever after first establishing a listening
 * socket for our sss connection, binding it, and listening. Once setup,
 * it perpetually waits for incoming data to either the listening socket, or
 * (if a connection is active), the sss data socket. When data arrives,
 * the approrpriate routine is called to either accept/reject a connection
 * request, or process incoming data.
 */
void SSSSimpleSocketServerTask()
{
  int fd_listen, max_socket;
  struct sockaddr_in addr;
  static SSSConn conn;
  fd_set readfds;

  /*
   * Sockets primer...
   * The socket() call creates an endpoint for TCP of UDP communication. It
   * returns a descriptor (similar to a file descriptor) that we call fd_listen,
   * or, "the socket we're listening on for connection requests" in our sss
   * server example.
   *
   * Traditionally, in the Sockets API, PF_INET and AF_INET is used for the
   * protocol and address families respectively. However, there is usually only
   * 1 address per protocol family. Thus PF_INET and AF_INET can be interchanged.
   * In the case of NicheStack, only the use of AF_INET is supported.
   * PF_INET is not supported in NicheStack.
   */
  if ((fd_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE, (void *) "[sss_task] Socket creation failed");
  }

  /*
   * Sockets primer, continued...
   * Calling bind() associates a socket created with socket() to a particular IP
   * port and incoming address. In this case we're binding to SSS_PORT and to
   * INADDR_ANY address (allowing anyone to connect to us. Bind may fail for
   * various reasons, but the most common is that some other socket is bound to
   * the port we're requesting.
   */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SSS_PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if ((bind(fd_listen,(struct sockaddr *)&addr,sizeof(addr))) < 0)
  {
    alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE, (void *) "[sss_task] Bind failed");
  }

  /*
   * Sockets primer, continued...
   * The listen socket is a socket which is waiting for incoming connections.
   * This call to listen will block (i.e. not return) until someone tries to
   * connect to this port.
   */
  if ((listen(fd_listen,1)) < 0)
  {
    alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE, (void *) "[sss_task] Listen failed");
  }

  /* At this point we have successfully created a socket which is listening
   * on SSS_PORT for connection requests from any remote address.
   */
  sss_reset_connection(&conn);
  printf("[sss_task] Simple Socket Server listening on port %d\n", SSS_PORT);

  while(1)
  {
    /*
     * For those not familiar with sockets programming...
     * The select() call below basically tells the TCPIP stack to return
     * from this call when any of the events I have expressed an interest
     * in happen (it blocks until our call to select() is satisfied).
     *
     * In the call below we're only interested in either someone trying to
     * connect to us, or data being available to read on a socket, both of
     * these are a read event as far as select is called.
     *
     * The sockets we're interested in are passed in in the readfds
     * parameter, the format of the readfds is implementation dependant
     * Hence there are standard MACROs for setting/reading the values:
     *
     *   FD_ZERO  - Zero's out the sockets we're interested in
     *   FD_SET   - Adds a socket to those we're interested in
     *   FD_ISSET - Tests whether the chosen socket is set
     */
    FD_ZERO(&readfds);
    FD_SET(fd_listen, &readfds);
    max_socket = fd_listen+1;

    if (conn.fd != -1)
    {
      FD_SET(conn.fd, &readfds);
      if (max_socket <= conn.fd)
      {
        max_socket = conn.fd+1;
      }
    }
    printf("preselect\n");
    select(max_socket, &readfds, NULL, NULL, NULL);
    printf("postselect\n");
    /*
     * If fd_listen (the listening socket we originally created in this thread
     * is "set" in readfs, then we have an incoming connection request. We'll
     * call a routine to explicitly accept or deny the incoming connection
     * request (in this example, we accept a single connection and reject any
     * others that come in while the connection is open).
     */
    if (FD_ISSET(fd_listen, &readfds))
    {
      sss_handle_accept(fd_listen, &conn);
    }
    /*
     * If sss_handle_accept() accepts the connection, it creates *another*
     * socket for sending/receiving data over sss. Note that this socket is
     * independant of the listening socket we created above. This socket's
     * descriptor is stored in conn.fd. If conn.fs is set in readfs... we have
     * incoming data for our sss server, and we call our receiver routine
     * to process it.
     */
    else
    {
    	printf("elsefdisset\n");
      if ((conn.fd != -1) && FD_ISSET(conn.fd, &readfds))
      {
    	  printf("handlerecieve\n");
        sss_handle_receive(&conn);
      }
    }
  } /* while(1) */
}
