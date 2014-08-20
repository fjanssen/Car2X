/*
* CarProtocol.h
*
* Created on: 17.11.2013
* Author: Florian
*/

#ifndef CARPROTOCOL_H_
#define CARPROTOCOL_H_

//define CARP MSG IDs
#define CARP_MSGID_WELCOME 				0x01
#define CARP_MSGID_MOTORVELOCITY 		0x04
#define CARP_MSGID_MOTORMEASUREMENT		0x05
#define CARP_MSGID_ULTRASOUNDSENSOR 	0x08
#define CARP_MSGID_ACCELERATIONSENSOR 	0x09
#define CARP_MSGID_ADCSENSOR 			0x0A

//define Car2X Message IDs
#define C2X_MSGID_EMERGENCY_BRAKE	 0x20
#define C2X_MSGID_CONTROL			 0x30
#define C2X_MSGID_INFO_STATE 		 0x40
#define C2X_MSGID_INFO_SENSORS		 0x50
#define C2X_MSGID_REMOTE_CONTROL 	 0x60

// Export interfaces
#include <alt_types.h>
#include "CarMessage.h"


/*
* Class CCarProtocol.
* This class manages the complete communication protocol. Each protocol object consists of a protocol-header
* and a list of messages (see CarMessage).
*
* Note: Due to some renaming conflicts there are the following synonyms:
* CarProtocol = Packet
* CarMessage = Message
* The fields in CarProtocol and CarMessage may have the same name. Make sure that you are in the right class!
*
* The total structure of a packet looks like:
*
* 1st Byte | 2nd Byte | 3rd Byte | 4th Byte
* ---------|----------|----------|-----------
* 'C' | 'A' | 'R' | 'P'
* PacketNumber | PayloadLength
* ---------|----------|----------|-----------
* P A Y L O A D
*
* 'C''A''R''P': Start sequence of the packet to detect a packet in the incoming byte-stream.
* PacketNumber: Consecutive increasing 16 bit number which works as an ID. The number is never changed by the
* Nios2, only by the central ECU (Linux-PC). Thereby the central ECU can detect a protocol fail
* if the response packet has not the same PacketNumber as the request packet.
* Please remember the wrap around after the PacketNumber 65535!
* PayloadLength: Total length of the payload in Bytes. This length information contains not the packet-header length!
*
* The payload contains at least one message and max. 8 messages. All messages start at a multiple of 4 assuming
* that all messages have a multiple of 4 as length. There must be no gap between two messages!!
*
*
* The order of the messages in a packet is important:
* Contains the packet a WelcomeMessage this message as to be the first. All other messages in this packet will
* be ignored!
*
* Otherwise the first message is the most important followed by the second and so on... See main.cpp for the
* meaning of important.
* Note: As the velocity-message is the most important in normal mode it will be assumed to be the first message!
* See also the main file for possible side-effects on the speed control.
*
*
*/
class CCarProtocol
{
public:
/*
* Constructor which fills the new object with data from the given byte array.
* Note: Even if there are more packets in the byte stream, only the first occurrence is used. All other
* packets will be ignored!
*
* pPacket: byte array containing the byte (network) representation of the packet.
* iLength: length of the byte stream.
*/
CCarProtocol(alt_u8 *pPacket, int iLength);

/*
* Constructor which packs the given messages to a new packet. This constructor is primarily called by the
* central ECU (Linux-PC).
*
* uiPacketNumber: packet number of the new packet. Don't forget to increase afterwards!
* pMessages: array of pointer (references) to the CarMessages.
* uiMessageCount: length of the array above.
*/
CCarProtocol(alt_u16 uiPacketNumber, CCarMessage **pMessages, alt_u32 uiMessageCount);

/*
* Destructor which calls the destructors of all CarMessage objects if necessary.
*/
virtual ~CCarProtocol();

/*
* Returns m_bValid.
*/
bool isValid();

/*
* Returns the total length of complete packet (packet-header + payload).
* Please note that this call has only O(n) but avoid multiple calls.
*/
alt_u32 getLength();

/*
* Returns the complete byte (network) representation of this packet including
* packet-header and payload (messages).
* Returns also m_bValid.
*/
bool getBytes(alt_u8 *pPacket);


/*
* Returns a pointer to the nth message in this packet. First message has n = 0!
* Is n >= m_uiMessageCount then a 0 is returned, otherwise the pointer to the
* message object.
*/
CCarMessage *getNthMessage(alt_u32 uiIdx);

/*
* Returns m_uiMessageCount.
*/
alt_u32 getMessageCount();

// Additional getter methods
alt_u16 getUiPacketNumber() const {
return m_uiPacketNumber;
}

bool isBThereIsMore() const {
return m_bThereIsMore;
}

private:

bool m_bValid;	// True if the packet was successfully generated / parsed.
bool m_bThereIsMore;	// True if the packet was partially parsed but there is something missing in the byte array.
alt_u16 m_uiPacketNumber;	// The packet number given in the packet-header.

CCarMessage *m_pMessages[8];	// Array of the pointer to the messages which are in this packet.
alt_u32	m_uiMessageCount;	// Count of messages in this packet.

/*
* Parsing method called by the constructors.
* Important note:
* >>>>>> You have to edit this method if there are new sensors / messages <<<<<
*
* Detailed comment in the .cpp file!
*/
void parsePacket(alt_u8 *pPacket, int iLength);

};

#endif /* CARPROTOCOL_H_ */
