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
#include "ip.h"

//CarProtocol: Used to parse the received bytes from the TCP connection into a Message
#include "CarProtocol.h"
#include "CarMessage.h"

//use alt types
#include <alt_types.h>
#include "ErrHandler.h"

#include "pendingAnswers.cpp"

} // extern C

#include "MemController.h"

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
//end of message includes

#define CAR_HEADER_LENGTH 8

//static IPs of Wheels, sensors, camera...board IP is 192.168.0.200
#define IP_WHEEL_LF     "192.168.0.12"
#define IP_WHEEL_LR    "192.168.0.14"
#define IP_WHEEL_RF     "192.168.0.11"
#define IP_WHEEL_RR     "192.168.0.13"
#define IP_ULTRASOUND   "192.168.0.20"
#define IP_CAMERA       "192.168.0.110"

//WelcomeMsg handler
CWelcomeMessage * wheel_LF = NULL;
CWelcomeMessage * wheel_RF = NULL;
CWelcomeMessage *wheel_LR = NULL;
CWelcomeMessage * wheel_RR = NULL;
CWelcomeMessage * camera = NULL;
CWelcomeMessage * ultrasound = NULL;
int fd_LF=0,fd_LR=0,fd_RF=0,fd_RR=0,fd_CAM=0,fd_US=0;

/*
 * sss_reset_connection()
 *
 * This routine will, when called, reset our SSSConn struct's members
 * to a reliable initial state. Note that we set our socket (FD) number to
 * -1 to easily determine whether the connection is in a "reset, ready to go"
 * state.
 */
void sss_reset_connection(SSSConn* conn) {
	memset(conn, 0, sizeof(SSSConn));

	conn->fd = -1;
	conn->state = SSS_SOCKET::READY;
	//LOG_DEBUG("[RESET] wr_pos = %i    rx_buffer = %i",	conn->rx_wr_pos, conn->rx_buffer);
	conn->rx_wr_pos = conn->rx_buffer;
	//LOG_DEBUG("[RESET] after set::: wr_pos = %i rx_buffer = %i",conn->rx_wr_pos, conn->rx_buffer);
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
void sss_handle_accept(int listen_socket, SSSConn* conn) {
	int socket, len;
	struct sockaddr_in incoming_addr;
	unsigned long* addr_ptr = &incoming_addr.sin_addr.s_addr;
	len = sizeof(incoming_addr);

	if ((conn)->fd == -1) {
		if ((socket =
				accept(listen_socket,(struct sockaddr*)&incoming_addr,&len))
				< 0) {
			alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
					(void *) "[sss_handle_accept] accept failed");
		} else {
			(conn)->fd = socket;

			struct l2b ip;
			ip.ip.iplong = incoming_addr.sin_addr.s_addr;
			conn->ip1 = (alt_u8) ip.ip.ipchar[0];
			conn->ip2 = (alt_u8) ip.ip.ipchar[1];
			conn->ip3 = (alt_u8) ip.ip.ipchar[2];
			conn->ip4 = (alt_u8) ip.ip.ipchar[3];

			char* str_ip_addr = inet_ntoa(incoming_addr.sin_addr);

			LOG_DEBUG("[sss_handle_accept] accepted connection request from %s",
					str_ip_addr);

			//here: check the incoming IP ADDR: and set conn->client_type accordingly
			//make sure static IP defines in the top of this file are correct!

			if (!strcmp(str_ip_addr, IP_WHEEL_LF))
				conn->client_type = SSSConn::WHEEL_LF;
			else if (!strcmp(str_ip_addr, IP_WHEEL_LR))
				conn->client_type = SSSConn::WHEEL_LR;
			else if (!strcmp(str_ip_addr, IP_WHEEL_RF))
				conn->client_type = SSSConn::WHEEL_RF;
			else if (!strcmp(str_ip_addr, IP_WHEEL_RR))
				conn->client_type = SSSConn::WHEEL_RR;
			else if (!strcmp(str_ip_addr, IP_ULTRASOUND))
				conn->client_type = SSSConn::ULTRASOUND;
			else if (!strcmp(str_ip_addr, IP_CAMERA))
				conn->client_type = SSSConn::CAMERA;
			else
				conn->client_type = SSSConn::WIPORT;

			//LOG_DEBUG("ip: %s %d", str_ip_addr, conn->client_type);

		}
	} else {
		LOG_DEBUG("[sss_handle_accept] rejected connection request from %s",
				inet_ntoa(incoming_addr.sin_addr));
	}
	//LOG_DEBUG("[ACCEPT] wr_pos = %i    rx_buffer = %i",
	//		conn->rx_wr_pos, conn->rx_buffer);
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
void sss_exec_command(CCarProtocol * receivedPacket, SSSConn* conn,
		currEmReqAnswer* cERA, currRemCtrlAnswer* cRCA, currCCtrlAnswer* cCCA) {
	alt_u32 iMessageCount, i;
	MemController<CarState> sharedMem;
	CarState state;

	sharedMem = MemController<CarState>();

	if (!receivedPacket->isValid()) {
		LOG_DEBUG("the received packet was not generated successfully and cant be handled by sss_exec_command!");
		return;
	}

	iMessageCount = receivedPacket->getMessageCount();

	for (i = 0; i < iMessageCount; i++) {
		state = sharedMem.getLastElement(true);

		//handle each message separately
		CCarMessage *currentMessage = receivedPacket->getNthMessage(i);

		alt_u8 messageType = currentMessage->getType();

		if (state.currMode != OPMODE_PREOPERATIONAL) {
			LOG_DEBUG("message Type: %d",messageType);
			switch (messageType) {

			// MotorVelocity
			case CARP_MSGID_MOTORVELOCITY: {
				CMotorVelocityMessage *motorVelocityMessage =
						(CMotorVelocityMessage *) currentMessage;
				LOG_DEBUG("MotorVelMsg: Setting motor ctrl [%d] velocity to %d",	motorVelocityMessage->getSubType(), motorVelocityMessage->getIDesiredSpeed());
				switch(conn->client_type){
				case SSSConn::WHEEL_LF:{
					state.motorEcus[0].iCurrentSpeed=motorVelocityMessage->getICurrentSpeed();
					break;
				}
				case SSSConn::WHEEL_LR:{
					state.motorEcus[1].iCurrentSpeed=motorVelocityMessage->getICurrentSpeed();
					break;
				}
				case SSSConn::WHEEL_RF:{
					state.motorEcus[2].iCurrentSpeed=motorVelocityMessage->getICurrentSpeed();
					break;
				}
				case SSSConn::WHEEL_RR:{
					state.motorEcus[3].iCurrentSpeed=motorVelocityMessage->getICurrentSpeed();
					break;
				}
				default:{
					LOG_ERROR(ERR_COMM_INVALID_MSG,	"Received unsupported CMotorVelocityMessage with ID %d.",	conn->client_type);
					break;
				}
				}
				break;
			}

				// MotorMeasurement
			case CARP_MSGID_MOTORMEASUREMENT: {
				CMotorMeasurementMessage *motorMeasurememtMessage =
						(CMotorMeasurementMessage *) currentMessage;
				LOG_DEBUG("received MotorMeasurementMsg for clinetType: %d",conn->client_type);
				switch(conn->client_type){
				case SSSConn::WHEEL_LF:{
					state.motorEcus[0].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[0].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[0].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[0].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[0].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				case SSSConn::WHEEL_LR:{
					state.motorEcus[1].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[1].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[1].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[1].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[1].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				case SSSConn::WHEEL_RF:{
					state.motorEcus[2].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[2].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[2].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[2].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[2].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				case SSSConn::WHEEL_RR:{
					state.motorEcus[3].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[3].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[3].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[3].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[3].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				default:{
					LOG_ERROR(ERR_COMM_INVALID_MSG,	"Received unsupported CMotorMeasurementMsgmessage with ID %d.",	conn->client_type);
					break;
				}
				}
				break;
			}

			// Ultrasound-Sensor
			case CARP_MSGID_ULTRASOUNDSENSOR: {
				CUltrasoundDistanceMessage *ultrasoundDistanceMessage =
						(CUltrasoundDistanceMessage *) currentMessage;
				//TODO: not supported because Hardware missing-->get Hardware
				break;
			}

			// Acceleration-Sensor
			case CARP_MSGID_ACCELERATIONSENSOR: {
				CAccelerationValuesMessage *accelerationValuesMessage =
						(CAccelerationValuesMessage*) currentMessage;
				//TODO: not supported by nano boards-->modify nano boards
				break;
			}

			//ADC-Sensor
			case CARP_MSGID_ADCSENSOR: {
				// If subtype is 0 then it's a InfoMessage otherwise a ValuesMessage
				//TODO: not supported by nano boards-->modify nano boards
				if (currentMessage->getSubType() == 0)
					CADCInfoMessage *adcInfoMessage =
							(CADCInfoMessage *) currentMessage;
				else
					CADCValuesMessage *adcValuesMessage =
							(CADCValuesMessage *) currentMessage;
				break;
			}

			//*******************************************CAR2X MESSAGES:*******************************************
			// Remote control message
			case C2X_MSGID_REMOTE_CONTROL: {
				CRemoteControlMessage * remoteControlMessage =
						(CRemoteControlMessage *) currentMessage;
				LOG_DEBUG("RemoteControlMsg");
				if (remoteControlMessage->get_ipPart1() == 0
						&& remoteControlMessage->get_ipPart2() == 0
						&& remoteControlMessage->get_ipPart3() == 0
						&& remoteControlMessage->get_ipPart4() == 0) {
					state.reqMode = OPMODE_AUTODRIVE;
					LOG_DEBUG("Switching back to automatic control.");
				} else {
					state.reqMode = OPMODE_MANUDRIVE;
					LOG_DEBUG("Switching to manual control.");
				}
				state.reqip1 = remoteControlMessage->get_ipPart1();
				state.reqip2 = remoteControlMessage->get_ipPart2();
				state.reqip3 = remoteControlMessage->get_ipPart3();
				state.reqip4 = remoteControlMessage->get_ipPart4();
				state.counterComm++;

				LOG_DEBUG(
						"locked IP is: %d, %d, %d, %d requested IP is: %d, %d, %d, %d",
						state.ip1, state.ip2, state.ip3, state.ip4, state.reqip1, state.reqip2, state.reqip3, state.reqip4);

				//write message to list/queue
				if (cRCA->stateVersion > 0) {
					//reply old msg for outdated
					int payloadLength = sizeof(alt_u16) + 4 * sizeof(state.ip1);
					int answerLength = 4 + sizeof(state.counterCarControl)
							+ sizeof(state.counterComm) + sizeof(payloadLength)
							+ 1 + sizeof((alt_u8) C2X_MSGID_REMOTE_CONTROL)
							+ payloadLength;
					int offset = 4;

					//Allocate memory for the answer char array
					char* answer = (char*) malloc(answerLength);
					answer[0] = 'C';
					answer[1] = 'A';
					answer[2] = 'R';
					answer[3] = 'P';
					//controlcore state counter
					memcpy(answer + offset, &state.counterCarControl,
							sizeof(state.counterCarControl));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterCarControl));
					offset += sizeof(state.counterCarControl);
					//commcore state counter
					memcpy(answer + offset, &state.counterComm,
							sizeof(state.counterComm));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterComm));
					offset += sizeof(state.counterComm);
					//payloadlength
					memcpy(answer + offset, &payloadLength,
							sizeof(payloadLength));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(payloadLength));
					offset += sizeof(payloadLength);
					//type def
					answer[offset++] = 'O'; //'O' for outdated
					answer[offset++] = (alt_u8) C2X_MSGID_REMOTE_CONTROL;
					//packetID
					memcpy(answer + offset, &cRCA->msgID, sizeof(cRCA->msgID));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(cRCA->msgID));
					offset += sizeof(cRCA->msgID);
					//ip1
					memcpy(answer + offset, &state.ip1, sizeof(state.ip1));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.ip1));
					offset += sizeof(state.ip1);
					//ip2
					memcpy(answer + offset, &state.ip2, sizeof(state.ip2));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.ip2));
					offset += sizeof(state.ip2);
					//ip3
					memcpy(answer + offset, &state.ip3, sizeof(state.ip3));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.ip3));
					offset += sizeof(state.ip3);
					//ip4
					memcpy(answer + offset, &state.ip4, sizeof(state.ip4));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.ip4));
					offset += sizeof(state.ip4);

					//send msg
					send(cRCA->fd, answer, answerLength, 0);
					free(answer);
				}
				cRCA->fd = conn->fd;
				cRCA->stateVersion = state.counterComm;
				cRCA->msgID = receivedPacket->getUiPacketNumber();
				cRCA->ip1 = state.ip1;
				cRCA->ip2 = state.ip2;
				cRCA->ip3 = state.ip3;
				cRCA->ip4 = state.ip4;
				break;
			}
				// Control message
			case C2X_MSGID_CONTROL: {
				CControlMessage * carControlMessage =
						(CControlMessage *) currentMessage;
				LOG_DEBUG("CControlMsg");
				//check if control is allowed
				state.counterComm++;
				if ((state.ip1 != conn->ip1 || state.ip2 != conn->ip2
						|| state.ip3 != conn->ip3 || state.ip4 != conn->ip4)) {
					LOG_DEBUG(
							"Control Msg failed because control not allowed!");
					LOG_DEBUG(
							"locked IP is: %d, %d, %d, %d current IP is: %d, %d, %d, %d",
							state.ip1, state.ip2, state.ip3, state.ip4, conn->ip1, conn->ip2, conn->ip3, conn->ip4);

					//control not allowed-->send fail msg
					int payloadLength = sizeof(alt_u16) + 4 * sizeof(alt_u8);
					int answerLength = 4 + sizeof(state.counterCarControl)
							+ sizeof(state.counterComm) + sizeof(payloadLength)
							+ 1 + sizeof((alt_u8) C2X_MSGID_CONTROL)
							+ payloadLength;
					int offset = 4;

					//Allocate memory for the answer char array
					char* answer = (char*) malloc(answerLength);
					answer[0] = 'C';
					answer[1] = 'A';
					answer[2] = 'R';
					answer[3] = 'P';
					//controlcore state counter
					memcpy(answer + offset, &state.counterCarControl,
							sizeof(state.counterCarControl));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterCarControl));
					offset += sizeof(state.counterCarControl);
					//commcore state counter
					memcpy(answer + offset, &state.counterComm,
							sizeof(state.counterComm));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterComm));
					offset += sizeof(state.counterComm);
					//payloadlength
					memcpy(answer + offset, &payloadLength,
							sizeof(payloadLength));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(payloadLength));
					offset += sizeof(payloadLength);
					//type def
					answer[offset++] = 'F'; //'F' for failed
					answer[offset++] = (alt_u8) C2X_MSGID_CONTROL;
					//packetID
					memcpy(answer + offset, &cCCA->msgID, sizeof(cCCA->msgID));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(cCCA->msgID));
					offset += sizeof(cCCA->msgID);
					//v1
					memcpy(answer + offset, &state.motorEcus[0].iDesiredSpeed,
							sizeof(state.motorEcus[0].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[0].iDesiredSpeed));
					offset += sizeof(state.motorEcus[0].iDesiredSpeed);
					//v2
					memcpy(answer + offset, &state.motorEcus[1].iDesiredSpeed,
							sizeof(state.motorEcus[1].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[1].iDesiredSpeed));
					offset += sizeof(state.motorEcus[1].iDesiredSpeed);
					//v3
					memcpy(answer + offset, &state.motorEcus[2].iDesiredSpeed,
							sizeof(state.motorEcus[2].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[2].iDesiredSpeed));
					offset += sizeof(state.motorEcus[2].iDesiredSpeed);
					//v4
					memcpy(answer + offset, &state.motorEcus[3].iDesiredSpeed,
							sizeof(state.motorEcus[3].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[3].iDesiredSpeed));
					offset += sizeof(state.motorEcus[3].iDesiredSpeed);

					//send msg
					send(cCCA->fd, answer, answerLength, 0);
					free(answer);

					break;
				}

				state.reqVelocity.iFrontLeft =
						carControlMessage->get_siVelFrontLeft();
				state.reqVelocity.iFrontRight =
						carControlMessage->get_siVelFrontRight();
				state.reqVelocity.iRearLeft =
						carControlMessage->get_siVelRearLeft();
				state.reqVelocity.iRearRight =
						carControlMessage->get_siVelRearRight();
				LOG_DEBUG("Requested velocities: %d, %d, %d, %d",
						state.reqVelocity.iFrontLeft, state.reqVelocity.iFrontRight, state.reqVelocity.iRearLeft, state.reqVelocity.iRearRight);

				//write message to list/queue
				if (cCCA->stateVersion > 0) {
					//reply old msg for outdated
					int payloadLength = sizeof(alt_u16) + 4 * sizeof(alt_u8);
					int answerLength = 4 + sizeof(state.counterCarControl)
							+ sizeof(state.counterComm) + sizeof(payloadLength)
							+ 1 + sizeof((alt_u8) C2X_MSGID_CONTROL)
							+ payloadLength;
					int offset = 4;

					//Allocate memory for the answer char array
					char* answer = (char*) malloc(answerLength);
					answer[0] = 'C';
					answer[1] = 'A';
					answer[2] = 'R';
					answer[3] = 'P';
					//controlcore state counter
					memcpy(answer + offset, &state.counterCarControl,
							sizeof(state.counterCarControl));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterCarControl));
					offset += sizeof(state.counterCarControl);
					//commcore state counter
					memcpy(answer + offset, &state.counterComm,
							sizeof(state.counterComm));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterComm));
					offset += sizeof(state.counterComm);
					//payloadlength
					memcpy(answer + offset, &payloadLength,
							sizeof(payloadLength));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(payloadLength));
					offset += sizeof(payloadLength);
					//type def
					answer[offset++] = 'O'; //'O' for outdated
					answer[offset++] = (alt_u8) C2X_MSGID_CONTROL;
					//packetID
					memcpy(answer + offset, &cCCA->msgID, sizeof(cCCA->msgID));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(cCCA->msgID));
					offset += sizeof(cCCA->msgID);
					//v1
					memcpy(answer + offset, &state.motorEcus[0].iDesiredSpeed,
							sizeof(state.motorEcus[0].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[0].iDesiredSpeed));
					offset += sizeof(state.motorEcus[0].iDesiredSpeed);
					//v2
					memcpy(answer + offset, &state.motorEcus[1].iDesiredSpeed,
							sizeof(state.motorEcus[1].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[1].iDesiredSpeed));
					offset += sizeof(state.motorEcus[1].iDesiredSpeed);
					//v3
					memcpy(answer + offset, &state.motorEcus[2].iDesiredSpeed,
							sizeof(state.motorEcus[2].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[2].iDesiredSpeed));
					offset += sizeof(state.motorEcus[2].iDesiredSpeed);
					//v4
					memcpy(answer + offset, &state.motorEcus[3].iDesiredSpeed,
							sizeof(state.motorEcus[3].iDesiredSpeed));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.motorEcus[3].iDesiredSpeed));
					offset += sizeof(state.motorEcus[3].iDesiredSpeed);

					//send msg
					send(cCCA->fd, answer, answerLength, 0);
					free(answer);
				}
				cCCA->fd = conn->fd;
				cCCA->stateVersion = state.counterComm;
				cCCA->msgID = receivedPacket->getUiPacketNumber();
				cCCA->v1 = carControlMessage->get_siVelFrontRight();
				cCCA->v2 = carControlMessage->get_siVelFrontLeft();
				cCCA->v3 = carControlMessage->get_siVelRearRight();
				cCCA->v4 = carControlMessage->get_siVelRearLeft();

				break;
			}
			case C2X_MSGID_EMERGENCY_BRAKE: {
				CEmergencyBrakeMessage * emergencyMessage =
						(CEmergencyBrakeMessage *) currentMessage;
				LOG_DEBUG("EmergencyBrakeMsg");
				//update state
				state.reqMode = OPMODE_EMERGENCYSTOP;
				state.counterComm++;
				//write message to list/queue
				if (cERA->stateVersion > 0) {
					//reply old msg for outdated
					int payloadLength = sizeof(alt_u16);
					int answerLength = 4 + sizeof(state.counterCarControl)
							+ sizeof(state.counterComm) + sizeof(payloadLength)
							+ 1 + sizeof((alt_u8) C2X_MSGID_EMERGENCY_BRAKE)
							+ payloadLength;
					int offset = 4;

					//Allocate memory for the answer char array
					char* answer = (char*) malloc(answerLength);
					answer[0] = 'C';
					answer[1] = 'A';
					answer[2] = 'R';
					answer[3] = 'P';
					//controlcore state counter
					memcpy(answer + offset, &state.counterCarControl,
							sizeof(state.counterCarControl));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterCarControl));
					offset += sizeof(state.counterCarControl);
					//commcore state counter
					memcpy(answer + offset, &state.counterComm,
							sizeof(state.counterComm));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(state.counterComm));
					offset += sizeof(state.counterComm);
					//payloadlength
					memcpy(answer + offset, &payloadLength,
							sizeof(payloadLength));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(payloadLength));
					offset += sizeof(payloadLength);
					//type def
					answer[offset++] = 'O';
					answer[offset++] = (alt_u8) C2X_MSGID_EMERGENCY_BRAKE;
					//packetID
					memcpy(answer + offset, &cERA->msgID, sizeof(cERA->msgID));
					swapEndianess((alt_u8*) (answer + offset),
							(alt_u32) sizeof(cERA->msgID));
					offset += sizeof(cERA->msgID);

					//send msg
					send(cERA->fd, answer, answerLength, 0);
					free(answer);
				}
				cERA->fd = conn->fd;
				cERA->stateVersion = state.counterComm;
				cERA->msgID = receivedPacket->getUiPacketNumber();
				break;
			}
			case C2X_MSGID_INFO_STATE: {
				//calculate some lengths...
				//TODO:Test it!!!!
				LOG_DEBUG("InfoStateMsg");
				int payloadLength = sizeof(state.currMode)
						+ sizeof(state.iMaxSpeed) + sizeof(state.motorEcus[0])
						+ sizeof(state.motorEcus[1])
						+ sizeof(state.motorEcus[2])
						+ sizeof(state.motorEcus[3]) + 8 * sizeof(state.ip1)
						+ sizeof(state.reqMode + sizeof(state.reqVelocity));
				LOG_DEBUG("pl: %i", payloadLength);
				//'CARP'+ID{SVControl+SVComm}+payloadLenght(type+mode+velocities)+Type{'A' for acknowledgement + C2X_MSGID_INFO_STATE}+payload{iMaxSpeed+4xIPs+4xreqIPs+currentMode+reqMode+4xmotorECUs+reqVelocity}
				int answerLength = 4 + sizeof(state.counterCarControl)
						+ sizeof(state.counterComm) + sizeof(payloadLength) + 1
						+ sizeof((alt_u8) C2X_MSGID_INFO_STATE) + payloadLength;
				int offset = 4;

				//Allocate memory for the answer char array
				char* answer = (char*) malloc(answerLength);

				/* build answer char array following this pseudo pattern:
				 * char answer[] = {'C', 'A', 'R', 'P',state.counterCarControl,state.counterComm,payloadLength, 'A', C2X_MSGID_INFO_STATE, state.currMode,state.iMaxSpeed,(char)state.motorEcus[0],state.motorEcus[1],state.motorEcus[2],state.motorEcus[3]};
				 */

				answer[0] = 'C';
				answer[1] = 'A';
				answer[2] = 'R';
				answer[3] = 'P';
				//controlcore state counter
				memcpy(answer + offset, &state.counterCarControl,
						sizeof(state.counterCarControl));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.counterCarControl));
				offset += sizeof(state.counterCarControl);
				//commcore state counter
				memcpy(answer + offset, &state.counterComm,
						sizeof(state.counterComm));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.counterComm));
				offset += sizeof(state.counterComm);
				//payloadlength
				memcpy(answer + offset, &payloadLength, sizeof(payloadLength));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(payloadLength));
				offset += sizeof(payloadLength);
				//type def
				answer[offset++] = 'A';
				answer[offset++] = (alt_u8) C2X_MSGID_INFO_STATE;
				//iMaxSpeed
				memcpy(answer + offset, &state.iMaxSpeed,
						sizeof(state.iMaxSpeed));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.iMaxSpeed));
				offset += sizeof(state.iMaxSpeed);
				//1st ip
				memcpy(answer + offset, &state.ip1, sizeof(state.ip1));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.ip1));
				offset += sizeof(state.ip1);
				//2nd ip
				memcpy(answer + offset, &state.ip2, sizeof(state.ip2));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.ip2));
				offset += sizeof(state.ip2);
				//3rd ip
				memcpy(answer + offset, &state.ip3, sizeof(state.ip3));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.ip3));
				offset += sizeof(state.ip3);
				//4th ip
				memcpy(answer + offset, &state.ip4, sizeof(state.ip4));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.ip4));
				offset += sizeof(state.ip4);
				//1st reqip
				memcpy(answer + offset, &state.reqip1, sizeof(state.reqip1));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.reqip1));
				offset += sizeof(state.reqip1);
				//2nd reqip
				memcpy(answer + offset, &state.reqip2, sizeof(state.reqip2));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.reqip2));
				offset += sizeof(state.reqip2);
				//3rd reqip
				memcpy(answer + offset, &state.reqip3, sizeof(state.reqip3));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.reqip3));
				offset += sizeof(state.reqip3);
				//4th reqip
				memcpy(answer + offset, &state.reqip4, sizeof(state.reqip4));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.reqip4));
				offset += sizeof(state.reqip4);
				//current mode
				memcpy(answer + offset, &state.currMode,
						sizeof(state.currMode));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.currMode));
				offset += sizeof(state.currMode);
				//req mode
				memcpy(answer + offset, &state.reqMode, sizeof(state.reqMode));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.reqMode));
				offset += sizeof(state.reqMode);
				//1st ECU state
				memcpy(answer + offset, &state.motorEcus[0],
						sizeof(state.motorEcus[0]));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.motorEcus[0]));
				offset += sizeof(state.motorEcus[0]);
				//2nd ECU state
				memcpy(answer + offset, &state.motorEcus[1],
						sizeof(state.motorEcus[1]));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.motorEcus[1]));
				offset += sizeof(state.motorEcus[1]);
				//3rd ECU state
				memcpy(answer + offset, &state.motorEcus[2],
						sizeof(state.motorEcus[2]));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.motorEcus[2]));
				offset += sizeof(state.motorEcus[2]);
				//4th ECU state
				memcpy(answer + offset, &state.motorEcus[3],
						sizeof(state.motorEcus[3]));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.motorEcus[3]));
				offset += sizeof(state.motorEcus[3]);
				//req velocity
				memcpy(answer + offset, &state.reqVelocity,
						sizeof(state.reqVelocity));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.reqVelocity));
				offset += sizeof(state.reqVelocity);

				//send message:
				send(conn->fd, answer, answerLength, 0);
				free(answer);
				break;
			}
			case C2X_MSGID_INFO_SENSORS: {

				LOG_DEBUG("InfoSensorMsg");
				//calculate some lengths...
				int payloadLength = sizeof(state.usSensors[0])
						+ sizeof(state.usSensors[1]);
				//'CARP'+ID{SVControl+SVComm}+payloadLength(length of both sensor structs)+Type{'A' for acknowledgement + C2X_MSGID_INFO_SENSOR}+payload{2xsensor struct}
				int answerLength = 4 + sizeof(state.counterCarControl)
						+ sizeof(state.counterComm) + sizeof(payloadLength) + 1
						+ sizeof((alt_u8) C2X_MSGID_INFO_SENSORS)
						+ payloadLength;
				int offset = 4;

				//Allocate memory for the answer char array
				char* answer = (char*) malloc(answerLength);

				/* build answer char array following this pseudo pattern:
				 * char answer[] = {'C', 'A', 'R', 'P',state.counterCarControl,state.counterComm,payloadLength, 'A', C2X_MSGID_INFO_SENSOR, state.usSensors[0],state.usSensors[1]};
				 */

				answer[0] = 'C';
				answer[1] = 'A';
				answer[2] = 'R';
				answer[3] = 'P';
				//controlcore state counter
				memcpy(answer + offset, &state.counterCarControl,
						sizeof(state.counterCarControl));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.counterCarControl));
				offset += sizeof(state.counterCarControl);
				//commcore state counter
				memcpy(answer + offset, &state.counterComm,
						sizeof(state.counterComm));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.counterComm));
				offset += sizeof(state.counterComm);
				//payloadlength
				memcpy(answer + offset, &payloadLength, sizeof(payloadLength));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(payloadLength));
				offset += sizeof(payloadLength);
				//type def
				answer[offset++] = 'A';
				answer[offset++] = (alt_u8) C2X_MSGID_INFO_SENSORS;
				//1st sensor
				memcpy(answer + offset, &state.usSensors[0],
						sizeof(state.usSensors[0]));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.usSensors[0]));
				offset += sizeof(state.usSensors[0]);
				//2nd sensor
				memcpy(answer + offset, &state.usSensors[1],
						sizeof(state.usSensors[1]));
				swapEndianess((alt_u8*) (answer + offset),
						(alt_u32) sizeof(state.usSensors[1]));
				offset += sizeof(state.usSensors[1]);

				//test print:
				/*printf("Info Sensor answer %i: ",answerLength);
				 for (int i = 0; i < answerLength; i++) {
				 printf("%02x ", answer[i]&0xFF);
				 }
				 printf("\n");
				 */

				//send message:
				send(conn->fd, answer, answerLength, 0);
				free(answer);
				break;
			}
			default: {
				LOG_ERROR(ERR_COMM_INVALID_MSG,
						"Received unsupported message with ID %d.",
						messageType);
				break;
			}
			}
		} else {
			LOG_DEBUG("PREOPERATIONAL");
			if(state.reqMode != OPMODE_PREOPERATIONAL){

				CMotorMeasurementMessage *motorMeasurememtMessage =(CMotorMeasurementMessage *) currentMessage;
				LOG_DEBUG("received MotorMeasurementMsg for clientType: %d",conn->client_type);
				switch(conn->client_type){
				case SSSConn::WHEEL_LF:{
					state.motorEcus[0].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[0].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[0].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[0].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[0].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				case SSSConn::WHEEL_LR:{
					state.motorEcus[1].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[1].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[1].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[1].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[1].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				case SSSConn::WHEEL_RF:{
					state.motorEcus[2].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[2].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[2].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[2].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[2].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				case SSSConn::WHEEL_RR:{
					state.motorEcus[3].iMaxSpeed=motorMeasurememtMessage->getIMaxSpeed();
					state.motorEcus[3].iDType=motorMeasurememtMessage->getIDType();
					state.motorEcus[3].iIType=motorMeasurememtMessage->getIIType();
					state.motorEcus[3].iPType=motorMeasurememtMessage->getIPType();
					state.motorEcus[3].uiWheelCircumference=motorMeasurememtMessage->getUiWheelCircumference();
					break;
				}
				default:{
					LOG_ERROR(ERR_COMM_INVALID_MSG,	"Received unsupported CMotorMeasurementMsgmessage with ID %d.",	conn->client_type);
					break;
				}
				}

			}else{

			//WelcomeMessage
			if (messageType == CARP_MSGID_WELCOME) {
				switch (conn->client_type) {
				case SSSConn::WHEEL_RF:{
					LOG_DEBUG("WelcomeMsg RF");
					if(wheel_RF)delete(wheel_RF);
					wheel_RF = new CWelcomeMessage(* ((CWelcomeMessage *) currentMessage));
					wheel_RF->answerMessage(0x0);
					fd_RF=conn->fd;
					//send(cRCA->fd, (char *) welcomeMessage, 1, 0);
					break;
				}
				case SSSConn::WHEEL_LF:{
					LOG_DEBUG("WelcomeMsg LF");
					if(wheel_LF)delete(wheel_LF);
					wheel_LF = new CWelcomeMessage(* ((CWelcomeMessage *) currentMessage));
					wheel_LF->answerMessage(0x0);
					fd_LF=conn->fd;
					//send(cRCA->fd, (char *) welcomeMessage, 1, 0);
					break;
				}
				case SSSConn::WHEEL_LR:{
					LOG_DEBUG("WelcomeMsg LR");
					if(wheel_LR)delete(wheel_LR);
					wheel_LR = new CWelcomeMessage(* ((CWelcomeMessage *) currentMessage));
					wheel_LR->answerMessage(0x0);
					fd_LR=conn->fd;
					//send(cRCA->fd, (char *) welcomeMessage, 1, 0);
					break;
				}
				case SSSConn::WHEEL_RR:{
					LOG_DEBUG("WelcomeMsg RR");
					if(wheel_RR)delete(wheel_RR);
					wheel_RR = new CWelcomeMessage(* ((CWelcomeMessage *) currentMessage));
					wheel_RR->answerMessage(0x0);
					fd_RR=conn->fd;
					//send(cRCA->fd, (char *) welcomeMessage, 1, 0);
					break;
				}
				case SSSConn::CAMERA:{
					LOG_DEBUG("WelcomeMsg CAM");
					if(camera)delete(camera);
					camera = new CWelcomeMessage(* ((CWelcomeMessage *) currentMessage));
					camera->answerMessage(0x0);
					fd_CAM=conn->fd;
					//send(cRCA->fd, (char *) welcomeMessage, 1, 0);
					break;
				}
				case SSSConn::ULTRASOUND:{
					LOG_DEBUG("WelcomeMsg US");
					if(ultrasound)delete(ultrasound);
					ultrasound = new CWelcomeMessage(* ((CWelcomeMessage *) currentMessage));
					ultrasound->answerMessage(0x0);
					fd_US=conn->fd;
					//send(cRCA->fd, (char *) welcomeMessage, 1, 0);
					break;
				}
				default:{
					LOG_ERROR(ERR_COMM_INVALID_MSG,	"Received unsupported WelcomeMessage with clientType %d.",	conn->client_type);
					break;
				}
				}
			}
			}

		}

		sharedMem.pushElement(state);
	}

}

/*
 * Try to receive bytes on the given connection
 * Additionally updates rx_wr_position in the connection data structure
 * Returns the number of bytes received
 */
int receive_bytes(SSSConn* conn) {
	int rx_code = recv(conn->fd, (char *) conn->rx_wr_pos,
			SSS_RX_BUF_SIZE - (conn->rx_wr_pos - conn->rx_buffer) -1, 0);
	//LOG_DEBUG("rxcode = %i", rx_code);

//	int rx_code = recv(conn->fd,(char*) conn->rx_wr_pos,1024, 0);

	if (rx_code > 0) {
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
void sss_handle_receive_new(SSSConn* conn, currEmReqAnswer* cERA,
		currRemCtrlAnswer* cRCA, currCCtrlAnswer* cCCA) {

	//we know some data can be received on the connection => reveive it to rx_buffer (will automatically increment rx_wr_pos
	//note: bytes may only be received once in this function as we assert that there is data to be read, otherwise this function may block out other connections
	int iBytesReceived = receive_bytes(conn);

	//nothing received? => disconnect command
	if (iBytesReceived <= 0) {
		LOG_DEBUG("empty msg");
		conn->state = SSSConn::CLOSE;
		return;
	}

	//check if CARP is somewhere in the buffer and throw everything away until CARP is there
	int bytesInBuffer = conn->rx_wr_pos - conn->rx_buffer;
	LOG_DEBUG("new Msg with bytesInbuffer = %i", bytesInBuffer);
	//LOG_DEBUG("wr_pos = %i    rx_buffer = %i",
	//		conn->rx_wr_pos, conn->rx_buffer);
	//LOG_DEBUG("buffer[0] = %02x", conn->rx_buffer[bytesInBuffer]);
	//output
	//LOG_DEBUG("msg: ");
	//for (int i = 0; i < bytesInBuffer; i++) {
	//    LOG_DEBUG("%02x ", conn->rx_buffer[i]&0xFF);
	//}
	//LOG_DEBUG("");

	if (bytesInBuffer < 4)
		return;
	//LOG_DEBUG("header >= 4");

	while (bytesInBuffer >= 4) {

		if (!(conn->rx_buffer[0] == 'C' && conn->rx_buffer[1] == 'A'
				&& conn->rx_buffer[2] == 'R' && conn->rx_buffer[3] == 'P')) {
			//no valid message detected yet => shift buffer one to the left and check again
			conn->rx_wr_pos -= 1;
			memmove(conn->rx_buffer, conn->rx_buffer + 1, bytesInBuffer);

			//clear off last element that has already been shifted
			*(conn->rx_wr_pos) = 0;
			bytesInBuffer--;
		}

		else {
			break;
		}
	}

	//now CARP has been received: check if payload len has been received yet
	if (bytesInBuffer < 8)
		return;
	//LOG_DEBUG("header msg");

	//full header arrived, now parse payload length
	int iPayloadLength = conn->rx_buffer[6] << 8;
	iPayloadLength += conn->rx_buffer[7];

	//check if the whole payload has been received
	if (bytesInBuffer - CAR_HEADER_LENGTH < iPayloadLength)
		return;
	//LOG_DEBUG("payload msg");

	//parse the found CCarProtocol object
	CCarProtocol * parsedPacket = new CCarProtocol((alt_u8 *) conn->rx_buffer,
			iPayloadLength + CAR_HEADER_LENGTH);

	//clear the buffer: delete message from it:
	memmove(conn->rx_buffer,
			conn->rx_buffer + iPayloadLength + CAR_HEADER_LENGTH,
			bytesInBuffer - iPayloadLength - CAR_HEADER_LENGTH);
	conn->rx_wr_pos -= (iPayloadLength + CAR_HEADER_LENGTH);
	memset(conn->rx_wr_pos, 0, iPayloadLength + CAR_HEADER_LENGTH);

	//execute the command
	sss_exec_command(parsedPacket, conn, cERA, cRCA, cCCA);
	delete (parsedPacket);
	LOG_DEBUG("Msg executed!");
}

void swapEndianess(alt_u8 *pArray, alt_u32 iLength) {
	alt_u8 buffer;
	alt_u32 middle = iLength / 2;

	iLength--;
	for (alt_u32 i = 0; i < middle;) {
		buffer = pArray[i];
		pArray[i] = pArray[iLength];
		pArray[iLength] = buffer;
		i++;
		iLength--;
	}
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
void SSSSimpleSocketServerTask() {
	int fd_listen, max_socket;
	struct sockaddr_in addr;
	static std::vector<SSSConn *> conns;
	fd_set readfds;

	//init currMsgStructs

	struct currEmReqAnswer cERA;
	struct currRemCtrlAnswer cRCA;
	struct currCCtrlAnswer cCCA;
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
	if ((fd_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
				(void *) "[sss_task] Socket creation failed");
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

	if ((bind(fd_listen,(struct sockaddr *)&addr,sizeof(addr))) < 0) {
		alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
				(void *) "[sss_task] Bind failed");
	}

	/*
	 * Sockets primer, continued...
	 * The listen socket is a socket which is waiting for incoming connections.
	 * This call to listen will block (i.e. not return) until someone tries to
	 * connect to this port.
	 */
	if ((listen(fd_listen,1)) < 0) {
		alt_NetworkErrorHandler(EXPANDED_DIAGNOSIS_CODE,
				(void *) "[sss_task] Listen failed");
	}

	/* At this point we have successfully created a socket which is listening
	 * on SSS_PORT for connection requests from any remote address.
	 */
	LOG_DEBUG("[sss_task] Simple Socket Server listening on port %d", SSS_PORT);
	unsigned long test=0;

	while (1) {
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
		max_socket = fd_listen + 1;

		test=cticks;
		select(max_socket, &readfds, NULL, NULL, &((timeval){0,500000}));  //!!!This is timing out after a while...0.5s is minimum for tcp_sleep()...if shorter timeout required, modify tcp_sleep()
		//LOG_DEBUG("leave SELECT started= %d, cticks= %d", test,cticks);
		//select(max_socket, &readfds, NULL, NULL, NULL);  	//!!!This is blocking as long as no TCP action!!!

		//processAnswerMessages
		MemController<CarState> sharedMem;
		CarState state;
		sharedMem = MemController<CarState>();
		state = sharedMem.getLastElement(false);

		//emergency
		if (cERA.stateVersion > 0
				&& cERA.stateVersion <= state.counterCarControl) {
			//answer msg
			int payloadLength = sizeof(alt_u16);
			int answerLength = 4 + sizeof(state.counterCarControl)
					+ sizeof(state.counterComm) + sizeof(payloadLength) + 1
					+ sizeof((alt_u8) C2X_MSGID_EMERGENCY_BRAKE)
					+ payloadLength;
			int offset = 4;

			//Allocate memory for the answer char array
			char* answer = (char*) malloc(answerLength);
			answer[0] = 'C';
			answer[1] = 'A';
			answer[2] = 'R';
			answer[3] = 'P';
			//controlcore state counter
			memcpy(answer + offset, &state.counterCarControl,
					sizeof(state.counterCarControl));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.counterCarControl));
			offset += sizeof(state.counterCarControl);
			//commcore state counter
			memcpy(answer + offset, &state.counterComm,
					sizeof(state.counterComm));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.counterComm));
			offset += sizeof(state.counterComm);
			//payloadlength
			memcpy(answer + offset, &payloadLength, sizeof(payloadLength));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(payloadLength));
			offset += sizeof(payloadLength);
			//type def
			if (state.currMode == OPMODE_EMERGENCYSTOP) {
				answer[offset++] = 'A'; //success
				LOG_DEBUG("EmergencyBraking successful!");
			} else {
				answer[offset++] = 'F'; //fail
				LOG_DEBUG("EmergencyBraking failed!");
			}
			answer[offset++] = (alt_u8) C2X_MSGID_EMERGENCY_BRAKE;
			//packetID
			memcpy(answer + offset, &cERA.msgID, sizeof(cERA.msgID));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(cERA.msgID));
			offset += sizeof(cERA.msgID);

			//send msg
			send(cERA.fd, answer, answerLength, 0);
			free(answer);
			//set cERA back to zero
			cERA.fd = 0;
			cERA.stateVersion = 0;
			cERA.msgID = 0;
		}

		//remoteControl
		if (cRCA.stateVersion > 0
				&& cRCA.stateVersion <= state.counterCarControl) {
			//answer msg
			int payloadLength = sizeof(alt_u16) + 4 * sizeof(state.ip1);
			int answerLength = 4 + sizeof(state.counterCarControl)
					+ sizeof(state.counterComm) + sizeof(payloadLength) + 1
					+ sizeof((alt_u8) C2X_MSGID_REMOTE_CONTROL) + payloadLength;
			int offset = 4;

			//Allocate memory for the answer char array
			char* answer = (char*) malloc(answerLength);
			answer[0] = 'C';
			answer[1] = 'A';
			answer[2] = 'R';
			answer[3] = 'P';
			//controlcore state counter
			memcpy(answer + offset, &state.counterCarControl,
					sizeof(state.counterCarControl));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.counterCarControl));
			offset += sizeof(state.counterCarControl);
			//commcore state counter
			memcpy(answer + offset, &state.counterComm,
					sizeof(state.counterComm));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.counterComm));
			offset += sizeof(state.counterComm);
			//payloadlength
			memcpy(answer + offset, &payloadLength, sizeof(payloadLength));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(payloadLength));
			offset += sizeof(payloadLength);
			//type def
			if ((state.ip1 == cRCA.ip1 && state.ip2 == cRCA.ip2
					&& state.ip3 == cRCA.ip3 && state.ip4 == cRCA.ip4)
					|| (cRCA.ip1 == 0 && cRCA.ip2 == 0 && cRCA.ip3 == 0
							&& cRCA.ip4 == 0 && state.ip1 == VCIPPart1
							&& state.ip2 == VCIPPart2 && state.ip3 == VCIPPart3
							&& state.ip4 == VCIPPart4)) {
				answer[offset++] = 'A'; //success
				LOG_DEBUG("RemoteControlling successful!");
			} else {
				answer[offset++] = 'F'; //fail
				LOG_DEBUG("RemoteControlling failed!");
			}
			answer[offset++] = (alt_u8) C2X_MSGID_REMOTE_CONTROL;
			//packetID
			memcpy(answer + offset, &cRCA.msgID, sizeof(cRCA.msgID));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(cRCA.msgID));
			offset += sizeof(cRCA.msgID);
			//ip1
			memcpy(answer + offset, &state.ip1, sizeof(state.ip1));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.ip1));
			offset += sizeof(state.ip1);
			//ip2
			memcpy(answer + offset, &state.ip2, sizeof(state.ip2));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.ip2));
			offset += sizeof(state.ip2);
			//ip3
			memcpy(answer + offset, &state.ip3, sizeof(state.ip3));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.ip3));
			offset += sizeof(state.ip3);
			//ip4
			memcpy(answer + offset, &state.ip4, sizeof(state.ip4));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.ip4));
			offset += sizeof(state.ip4);

			//send msg
			send(cRCA.fd, answer, answerLength, 0);
			free(answer);

			//set cRCA back to zero
			cRCA.fd = 0;
			cRCA.stateVersion = 0;
			cRCA.msgID = 0;
			cRCA.ip1 = 0;
			cRCA.ip2 = 0;
			cRCA.ip3 = 0;
			cRCA.ip4 = 0;
		}

		//control msg
		if (cCCA.stateVersion > 0
				&& cCCA.stateVersion <= state.counterCarControl) {
			//answer msg
			int payloadLength = sizeof(alt_u16) + 4 * sizeof(alt_u8);
			int answerLength = 4 + sizeof(state.counterCarControl)
					+ sizeof(state.counterComm) + sizeof(payloadLength) + 1
					+ sizeof((alt_u8) C2X_MSGID_CONTROL) + payloadLength;
			int offset = 4;

			//Allocate memory for the answer char array
			char* answer = (char*) malloc(answerLength);
			answer[0] = 'C';
			answer[1] = 'A';
			answer[2] = 'R';
			answer[3] = 'P';
			//controlcore state counter
			memcpy(answer + offset, &state.counterCarControl,
					sizeof(state.counterCarControl));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.counterCarControl));
			offset += sizeof(state.counterCarControl);
			//commcore state counter
			memcpy(answer + offset, &state.counterComm,
					sizeof(state.counterComm));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.counterComm));
			offset += sizeof(state.counterComm);
			//payloadlength
			memcpy(answer + offset, &payloadLength, sizeof(payloadLength));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(payloadLength));
			offset += sizeof(payloadLength);
			//type def
			if (cCCA.v1 == state.motorEcus[0].iDesiredSpeed
					&& cCCA.v2 == state.motorEcus[1].iDesiredSpeed
					&& cCCA.v3 == state.motorEcus[2].iDesiredSpeed
					&& cCCA.v4 == state.motorEcus[3].iDesiredSpeed) {
				answer[offset++] = 'A'; //success
			} else {
				answer[offset++] = 'F'; //fail
			}

			answer[offset++] = (alt_u8) C2X_MSGID_CONTROL;
			//packetID
			memcpy(answer + offset, &cCCA.msgID, sizeof(cCCA.msgID));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(cCCA.msgID));
			offset += sizeof(cCCA.msgID);
			//v1
			memcpy(answer + offset, &state.motorEcus[0].iDesiredSpeed,
					sizeof(state.motorEcus[0].iDesiredSpeed));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.motorEcus[0].iDesiredSpeed));
			offset += sizeof(state.motorEcus[0].iDesiredSpeed);
			//v2
			memcpy(answer + offset, &state.motorEcus[1].iDesiredSpeed,
					sizeof(state.motorEcus[1].iDesiredSpeed));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.motorEcus[1].iDesiredSpeed));
			offset += sizeof(state.motorEcus[1].iDesiredSpeed);
			//v3
			memcpy(answer + offset, &state.motorEcus[2].iDesiredSpeed,
					sizeof(state.motorEcus[2].iDesiredSpeed));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.motorEcus[2].iDesiredSpeed));
			offset += sizeof(state.motorEcus[2].iDesiredSpeed);
			//v4
			memcpy(answer + offset, &state.motorEcus[3].iDesiredSpeed,
					sizeof(state.motorEcus[3].iDesiredSpeed));
			swapEndianess((alt_u8*) (answer + offset),
					(alt_u32) sizeof(state.motorEcus[3].iDesiredSpeed));
			offset += sizeof(state.motorEcus[3].iDesiredSpeed);

			//send msg
			send(cCCA.fd, answer, answerLength, 0);
			free(answer);

			//if state update successful: send motor values to the nano boards
			if (cCCA.v1 == state.motorEcus[0].iDesiredSpeed	&& cCCA.v2 == state.motorEcus[1].iDesiredSpeed	&& cCCA.v3 == state.motorEcus[2].iDesiredSpeed && cCCA.v4 == state.motorEcus[3].iDesiredSpeed) {
			//build messages for all4 wheels:
				//lfwheel
				CMotorVelocityMessage* tmpMsg1 = new CMotorVelocityMessage(state.motorEcus[0].iDesiredSpeed);
				CCarProtocol* tmpProtocol1=new CCarProtocol(0,(CCarMessage **) &tmpMsg1,1);
				alt_u8 * buf1 = (alt_u8 *) malloc(tmpProtocol1->getLength());
				tmpProtocol1->getBytes(buf1);
				LOG_DEBUG("lf built");
				//lrwheel
				CMotorVelocityMessage* tmpMsg2 = new CMotorVelocityMessage(state.motorEcus[1].iDesiredSpeed);
				CCarProtocol* tmpProtocol2=new CCarProtocol(0,(CCarMessage **) &tmpMsg2,1);
				alt_u8 * buf2 = (alt_u8 *) malloc(tmpProtocol2->getLength());
				tmpProtocol2->getBytes(buf2);
				LOG_DEBUG("lr built");
				//rfwheel
				CMotorVelocityMessage* tmpMsg3 = new CMotorVelocityMessage(state.motorEcus[2].iDesiredSpeed);
				CCarProtocol* tmpProtocol3=new CCarProtocol(0,(CCarMessage **) &tmpMsg3,1);
				alt_u8 * buf3 = (alt_u8 *) malloc(tmpProtocol3->getLength());
				tmpProtocol3->getBytes(buf3);
				LOG_DEBUG("rf built");
				//rrwheel
//				CMotorVelocityMessage* tmpMsg4 = new CMotorVelocityMessage(state.motorEcus[3].iDesiredSpeed);
//				CCarProtocol* tmpProtocol4=new CCarProtocol(0,(CCarMessage **) &tmpMsg4,1);
//				alt_u8 * buf4 = (alt_u8 *) malloc(tmpProtocol4->getLength());
//				tmpProtocol4->getBytes(buf4);
//				LOG_DEBUG("rr built");

				LOG_DEBUG("CMotorVelMsgs built");

				//send CMVelMessages
				send(fd_LF, (char*) buf1, tmpProtocol1->getLength(), 0);
				//send(fd_RF, (char*) buf2, tmpProtocol2->getLength(), 0);
				//send(fd_LR, (char*) buf3, tmpProtocol3->getLength(), 0);
				//send(fd_RR, (char*) buf4, tmpProtocol4->getLength(), 0);

				//free & delete
				free (buf1);
				free (buf2);
				free (buf3);
				//free (buf4);
				delete tmpMsg1;
				delete tmpMsg2;
				delete tmpMsg3;
				//delete tmpMsg4;
				delete tmpProtocol1;
				delete tmpProtocol2;
				delete tmpProtocol3;
				//delete tmpProtocol3;


			}

			//set cCCA back to zero
			cCCA.fd = 0;
			cCCA.stateVersion = 0;
			cCCA.msgID = 0;
			cCCA.v1 = 0;
			cCCA.v2 = 0;
			cCCA.v3 = 0;
			cCCA.v4 = 0;



		}

		/*
		 * If fd_listen (the listening socket we originally created in this thread
		 * is "set" in readfs, then we have an incoming connection request. We'll
		 * call a routine to explicitly accept or deny the incoming connection
		 * request (in this example, we accept a single connection and reject any
		 * others that come in while the connection is open).
		 */
		if (FD_ISSET(fd_listen, &readfds)) {
			SSSConn * new_conn = new SSSConn;
			sss_reset_connection(new_conn);
			sss_handle_accept(fd_listen, new_conn);
			conns.push_back(new_conn);
		}
		/*
		 * If sss_handle_accept() accepts the connection, it creates *another*
		 * socket for sending/receiving data over sss. Note that this socket is
		 * independant of the listening socket we created above. This socket's
		 * descriptor is stored in conn.fd. If conn.fs is set in readfs... we have
		 * incoming data for our sss server, and we call our receiver routine
		 * to process it.
		 */
		else {
			for (int i = 0; i < conns.size(); i++) {
				if ((conns[i]->fd != -1) && FD_ISSET(conns[i]->fd, &readfds)) {
					sss_handle_receive_new(conns[i], &cERA, &cRCA, &cCCA);
				}
			}
		}

		//check in PREOPERATIONAL mode if all WelcomeMessages are received
		//if(state.currMode==OPMODE_PREOPERATIONAL&&wheel_LF!=NULL&&wheel_LR!=NULL&&wheel_RF!=NULL&&wheel_RR!=NULL){  ...because RR nano board missing
		LOG_DEBUG("Wheels: %d, %d, %d, %d",wheel_LF,wheel_LR, wheel_RF,wheel_RR);
		LOG_DEBUG("Modes(currrent, req): %d, %d",state.currMode,state.reqMode);
		//if(state.currMode==OPMODE_PREOPERATIONAL && state.reqMode!=OPMODE_IDLE && wheel_LF!=NULL && wheel_LR!=NULL && wheel_RF!=NULL && wheel_RR != NULL){
		if(state.currMode==OPMODE_PREOPERATIONAL && state.reqMode!=OPMODE_IDLE && wheel_LF!=NULL){


			//build welcome Messages
			//LOG_DEBUG("start building");
			//lfwheel
			CCarProtocol* tmpProtocol1=new CCarProtocol(0,(CCarMessage **) &wheel_LF,1);
			LOG_DEBUG("lf %d");
			for(int i = 0 ; i < 10000; i++) {;}
			alt_u8 * buf1 = (alt_u8 *) malloc(tmpProtocol1->getLength());
			//alt_u8 buf1[256];
			tmpProtocol1->getBytes(buf1);
			//LOG_DEBUG("lf built");
			for(int i = 0 ; i < 10000; i++) {;}
//			//rfwheel
//			CCarProtocol* tmpProtocol2=new CCarProtocol(0,(CCarMessage **) &wheel_RF,1);
//			alt_u8 * buf2 = (alt_u8 *) malloc(tmpProtocol2->getLength());
//			//alt_u8 buf2[256];
//			tmpProtocol1->getBytes(buf2);
//			LOG_DEBUG("rf built");
//			for(int i = 0 ; i < 10000; i++) {;}
//
//			//lrwheel
//			CCarProtocol* tmpProtocol3=new CCarProtocol(0,(CCarMessage **) &wheel_LR,1);
//			alt_u8 * buf3 = (alt_u8 *) malloc(tmpProtocol3->getLength());
//			//alt_u8 buf3[256];
//			tmpProtocol3->getBytes(buf3);
//			LOG_DEBUG("lr built");
//			for(int i = 0 ; i < 10000; i++) {;}

			//rrwheel
			//CCarProtocol* tmpProtocol4=new CCarProtocol(0,(CCarMessage **) &wheel_RR,1);
			//alt_u8 * buf4 = (alt_u8 *) malloc(tmpProtocol4->getLength());
			//tmpProtocol1->getBytes(buf4);
			//LOG_DEBUG("rr built");
			//LOG_DEBUG("Welcomes built");

			//send Welcome MEssages
			send(fd_LF, (char*) buf1, tmpProtocol1->getLength(), 0);
			//send(fd_RF, (char*) buf2, tmpProtocol2->getLength(), 0);
			//send(fd_LR, (char*) buf3, tmpProtocol3->getLength(), 0);
			//send(fd_RR, (char*) buf4, tmpProtocol4->getLength(), 0);

			LOG_DEBUG("Welcomes sent");



			//let the nanoboard process the messages
			for(int i=0;i<10000000;i++){;}

			//create empty msg+protocol
			CMotorMeasurementMessage* tmpMsg= new CMotorMeasurementMessage();
			tmpProtocol1=new CCarProtocol(0,(CCarMessage **) &tmpMsg,1);
			free (buf1);
			buf1 = (alt_u8 *) malloc(tmpProtocol1->getLength());
			tmpProtocol1->getBytes(buf1);

			//LOG_DEBUG("CMeasurements built");

			//send empty msgs
			send(fd_LF, (char*) buf1, tmpProtocol1->getLength(), 0);
			//send(fd_RF, (char*) buf1, tmpProtocol1->getLength(), 0);
			//send(fd_LR, (char*) buf1, tmpProtocol1->getLength(), 0);
			//send(fd_RR, (char*) buf1, tmpProtocol1->getLength(), 0);

			LOG_DEBUG("CMeasurements sent");
			for(int i=0;i<10000000;i++){;}
			//free & delete
			free (buf1);
			//free (buf2);
			//free (buf3);
			//free (buf4);
			delete tmpProtocol1;
			//delete tmpProtocol2;
			//delete tmpProtocol3;
			//delete tmpProtocol4;


			//LOG_DEBUG("delete & free");

			//set state to IDLE
			state = sharedMem.getLastElement(true);
			state.reqMode=OPMODE_IDLE;
			sharedMem.pushElement(state);

			LOG_DEBUG("Enter state IDLE");

		}

		//check for each connection if its valid => set it
		for (unsigned int i = 0; i < conns.size(); i++) {
			//check if a connection should be closed here, close it and delete it from vector
			if (conns[i]->state == SSSConn::CLOSE) {
				close(conns[i]->fd);
				delete conns[i];
				conns.erase(conns.begin() + i);
			}

			if (conns[i]->fd != -1) {
				FD_SET(conns[i]->fd, &readfds);
				max_socket++;
			}

		}





	} /* while(1) */
}
