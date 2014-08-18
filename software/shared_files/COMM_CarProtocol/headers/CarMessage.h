/*
 * CarMessage.h
 *
 *  Created on: 05.01.2014
 *      Author: Florian
 */

#ifndef CARMESSAGE_H_
#define CARMESSAGE_H_

// Shared includes for all subclasses
#include <alt_types.h>
#include "../etc/utility.h"

/*
 * Class CCarMessage.
 * This class represents a single basic message. It consists of a message-header and a message-body.
 * The message-header is implemented in this super-class. Due to different body-types the body must
 * be implemented in the subclasses.
 *
 * Structure of a simple message:
 * 1st Byte | 2nd Byte | 3rd Byte | 4th Byte
 * ---------|----------|----------|-----------
 * Type     | Length   | SubType  | Flags
 *    P     A     Y     L     O     A     D
 *
 * Type is the ID of the message class. The type follows this rule:
 * Types between 0 and 3 are for NETWORKING (such as WelcomeMessage)
 * Types between 4 and 7 are BASIC messages and have to be understood by every networking client
 * Types between 8 and X are GENERAL purpose messages
 *
 * Length = Length of header (always 4 bytes) + Length of PAYLOAD
 * The Length of request and answer should always be identical!
 *
 * If a sensor requires more than one message type, SubType distinguishes between this messages.
 * Is there just one message type this field should be 0.
 *
 * Flags: Bits are numbered from 0 (least significant bit) to 7:
 * Bit 0:  Request(0) / Answer(1)
 * ...
 */
class CCarMessage
{
public:
	/*
	 * Basic Constructor which initialize the member fields.
	 */
	CCarMessage();

	/*
	 * Constructor which regenerate a message object out of the given byte (char) array.
	 * Note: There can be more than one message in the array. Only the first occurrence is used!
	 * pMessage: contains one or more messages.
	 * iLength: length of the array
	 */
	CCarMessage(alt_u8 *pMessage, int iLength);

	/*
	 * Constructor which initializes the member fields with the given values.
	 */
	CCarMessage(alt_u8 uiType, alt_u8 uiLength, bool bResponse);

	/*
	 * Destructor. (Empty implementation)
	 */
	virtual ~CCarMessage();

	/*
	 * This method is called during the message cycle.
	 * Usually it starts a measurement or gives an other command to one of the sensors.
	 * Of course there should be a result value. This result is copied to the message via
	 * a optional answer(..) method.
	 *
	 * This method should be strictly RUNTIME LIMITED!!!
	 * If it takes too long, the timed cycle will be broken!
	 *
	 * This method can also be empty.
	 *
	 * Note: Because of different build types use CENTRAL_ECU_BUILD as an include-guard to prevent the
	 * include of sensor-drivers in Linux-PC build.
	 */
	virtual void doAction();

	/*
	 * Gets the byte representation  of the message object.
	 * pMessage: Buffer for the bytes
	 * return: value of m_bValid;
	 */
	virtual bool getBytes(alt_u8 *pMessage);

	/*
	 * Gets the total length of this message.
	 * This value is the same as in the Length field of the header!
	 * return: length of the message (4 byte header + payload length)
	 */
	virtual alt_u32 getLength();

	/*
	 * Gets the message type
	 */
	alt_u8 getType();

	/*
	 * Gets the message subtype
	 */
	alt_u8 getSubType();

	/*
	 * Is this message valid?
	 */
	bool isValid();

protected:
	// Member fields, representing the message header.
	alt_u8 m_uiType;
	alt_u8 m_uiLength;
	alt_u8 m_uiSubType;
	alt_u8 m_uiFlags;

	bool m_bValid; // Message valid or not?

	/*
	 * Method sugar used by the constructors.
	 */
	void setHeader(alt_u8 uiType, alt_u8 uiLength, bool bResponse);
	void setHeader(alt_u8 uiType, alt_u8 uiLength, alt_u8 uiSubType, bool bResponse);
	void parseHeader(alt_u8 *pMessage, int iLength);
	alt_32 writeHeaderToBuffer(alt_u8 *pMessage, int iLength);

};

#endif /* CARMESSAGE_H_ */
