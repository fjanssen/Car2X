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

#include <vector>
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

//static IPs of Wheels, sensors, camera
#define IP_WHEEL_LF     "0.0.0.0"
#define IP_WHEEL_LB     "0.0.0.0"
#define IP_WHEEL_RF     "0.0.0.0"
#define IP_WHEEL_RB     "0.0.0.0"
#define IP_ULTRASOUND   "0.0.0.0"
#define IP_CAMERA       "0.0.0.0"

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
    printf("[RESET] wr_pos = %i    rx_buffer = %i\n",conn->rx_wr_pos,conn->rx_buffer);
    conn->rx_wr_pos = conn->rx_buffer;
    printf("[RESET] after set::: wr_pos = %i    rx_buffer = %i\n",conn->rx_wr_pos,conn->rx_buffer);
    conn->client_type = SSS_SOCKET::UNKNOWN;
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
            
            char* str_ip_addr = inet_ntoa(incoming_addr.sin_addr);
            
            printf("[sss_handle_accept] accepted connection request from %s\n",
                   str_ip_addr);
            
            //here: check the incoming IP ADDR: and set conn->client_type accordingly
            //make sure static IP defines in the top of this file are correct!
            
                 if(strcmp(str_ip_addr,IP_WHEEL_LF))    conn->client_type = SSSConn::WHEEL_LF;
            else if(strcmp(str_ip_addr,IP_WHEEL_LF))    conn->client_type = SSSConn::WHEEL_LB;
            else if(strcmp(str_ip_addr,IP_WHEEL_LF))    conn->client_type = SSSConn::WHEEL_RF;
            else if(strcmp(str_ip_addr,IP_WHEEL_LF))    conn->client_type = SSSConn::WHEEL_RB;
            else if(strcmp(str_ip_addr,IP_WHEEL_LF))  conn->client_type = SSSConn::ULTRASOUND;
            else if(strcmp(str_ip_addr,IP_WHEEL_LF))      conn->client_type = SSSConn::CAMERA;
            else                                         conn->client_type = SSSConn::WIPORT;

            
        }
    }
    else
    {
        printf("[sss_handle_accept] rejected connection request from %s\n",
               inet_ntoa(incoming_addr.sin_addr));
    }
    printf("[ACCEPT] wr_pos = %i    rx_buffer = %i\n",conn->rx_wr_pos,conn->rx_buffer);
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
void sss_exec_command(CCarProtocol * receivedPacket,SSSConn* conn)
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
    printf("rxcode = %i\n",rx_code);
//	int rx_code = recv(conn->fd,(char*) conn->rx_wr_pos,1024, 0);

	if(rx_code > 0)
	{
        conn->rx_wr_pos += rx_code;
	}
    
	return rx_code;
}

//int receive_bytes_neu(SSSConn* conn)



/*
 * sss_handle_receive_new()
 *
 * This method is called on a connection every time data can be received (decided by the select command)
 * reveive_bytes(conn) receives the bytes once in the beginning to the buffer.
 * Then this buffer is read up to the point its possible yet (the whole message might not arrive at once)
 *
 * If a whole message has been received we parse it as a CCarProtocol object and execute the command.   
 * Then we need to clear the buffer to avoid overflow.
 */
void sss_handle_receive_new(SSSConn* conn)
{

    //we know some data can be received on the connection => reveive it to rx_buffer (will automatically increment rx_wr_pos
    //note: bytes may only be received once in this function as we assert that there is data to be read, otherwise this function may block out other connections 
    int iBytesReceived = receive_bytes(conn);
    
    //nothing received? => disconnect command
    if(iBytesReceived == 0)
    {
    	printf("empty msg\n");
        conn->state = SSSConn::CLOSE;
        return;
    }




    //check if CARP is somewhere in the buffer and throw everything away until CARP is there
    int bytesInBuffer =conn->rx_wr_pos - conn->rx_buffer ;
    printf("bytesInbuffer = %i\n",bytesInBuffer);
    printf("wr_pos = %i    rx_buffer = %i\n",conn->rx_wr_pos, conn->rx_buffer);
    printf("buffer[0] = %02x\n",conn->rx_buffer[bytesInBuffer]);
    //output
                printf("msg: ");
                for (int i = 0; i < bytesInBuffer; i++) {
                    printf("%02x ", conn->rx_buffer[i]&0xFF);
                }
                printf("\n");

    if(bytesInBuffer < 4) return;
    printf("header >= 4\n");

    while(bytesInBuffer >= 4)
    {
        
        if (!(conn->rx_buffer[0] == 'C' && conn->rx_buffer[1] == 'A' && conn->rx_buffer[2] == 'R' && conn->rx_buffer[3] == 'P'))
        {
            //no valid message detected yet => shift buffer one to the left and check again
            conn->rx_wr_pos -= 1;
            memmove(conn->rx_buffer,conn->rx_buffer+1,bytesInBuffer);
            
            //clear off last element that has already been shifted
            *(conn->rx_wr_pos) = 0;
            bytesInBuffer--;
        }
    }
    
    //now CARP has been received: check if payload len has been received yet
    if(bytesInBuffer < 8)return;
    printf("header msg\n");
    
    //full header arrived, now parse payload length
    int 	iPayloadLength  = conn->rx_buffer[6] << 8;
    iPayloadLength += conn->rx_buffer[7];
    
    //check if the whole payload has been received
    if(bytesInBuffer - CAR_HEADER_LENGTH < iPayloadLength)return;
    printf("payload msg\n");
    
    //parse the found CCarProtocol object
    CCarProtocol * parsedPacket = new CCarProtocol((alt_u8 *)conn->rx_buffer,iPayloadLength+CAR_HEADER_LENGTH);
    
    //send dummy msg back(for debug reasons)
    send(conn->fd,(char*)conn->rx_buffer,iPayloadLength+CAR_HEADER_LENGTH,0);

    //clear the buffer: delete message from it:
    memmove(conn->rx_buffer,conn->rx_buffer+iPayloadLength+CAR_HEADER_LENGTH,bytesInBuffer-iPayloadLength-CAR_HEADER_LENGTH);
    conn->rx_wr_pos -= (iPayloadLength+CAR_HEADER_LENGTH);
    memset(conn->rx_wr_pos,0,iPayloadLength+CAR_HEADER_LENGTH);
    
    //execute the command
    sss_exec_command(parsedPacket,conn);
    delete(parsedPacket);
    printf("msg executed!\n");
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
    static std::vector<SSSConn> conns;
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
        
//        printf("conns: %i\n",conns.size());

        //check for each connection if its valid => set it
        for(int i = 0;i < conns.size();i++)
        {
        	//check if a connection should be closed here, close it and delete it from vector
        	if(conns[i].state == SSSConn::CLOSE)
        	{
        	    close(conns[i].fd);
        	    conns.erase(conns.begin()+i);
        	}

        	if (conns[i].fd != -1)
            {
                FD_SET(conns[i].fd, &readfds);
                max_socket++;
            }

        }
        

        select(max_socket, &readfds, NULL, NULL, NULL);

        /*
         * If fd_listen (the listening socket we originally created in this thread
         * is "set" in readfs, then we have an incoming connection request. We'll
         * call a routine to explicitly accept or deny the incoming connection
         * request (in this example, we accept a single connection and reject any
         * others that come in while the connection is open).
         */
        if (FD_ISSET(fd_listen, &readfds))
        {
            SSSConn new_conn;
            sss_reset_connection(&new_conn);
            sss_handle_accept(fd_listen, &new_conn);
            conns.push_back(new_conn);
            (conns[0]).rx_wr_pos = (conns[0]).rx_buffer;			//#TODO needs fixing, changes rx_buffer
            printf("[PUSH] wr_pos = %i    rx_buffer = %i\n",(conns[0]).rx_wr_pos,(conns[0]).rx_buffer);

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
            for(int i = 0;i < conns.size();i++)
            {
                if ((conns[i].fd != -1) && FD_ISSET(conns[i].fd, &readfds))
                {
                    sss_handle_receive_new(&(conns[i]));
                }
            }
        }
    } /* while(1) */
}
