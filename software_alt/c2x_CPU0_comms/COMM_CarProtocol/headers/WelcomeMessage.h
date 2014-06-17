/*
 * WelcomeMessage.h
 *
 *  Created on: 05.01.2014
 *      Author: Florian
 */

#ifndef WELCOMEMESSAGE_H_
#define WELCOMEMESSAGE_H_

#include "CarMessage.h"

/*
 * Class CWelcomeMessage derived from CCarMessage.
 * This class has two aims:
 *     Synchronize the 4 Motor-ECU with the central-ECU,
 *     inform the central-ECU about the messages which can be understood by this Motor-ECU.
 *
 * The central-ECU sends (at the same time) a WelcomeMessage to each Motor-ECU. The Motor-ECUs
 * answer with the same message but additional with a list of those messages which are available
 * at this ECU.
 *
 * The message has the following structure:
 *
 * 1st Byte   | 2nd Byte    | 3rd Byte    | 4th Byte
 * -----------|-------------|-------------|-------------
 * Type       | Length      | SubType     | Flags
 * -----------|-------------|-------------|-------------
 * FW Version | ECU Version | ECU Type    | ECU Type
 * Message1   | Message 2   | Message 3   | Message 4
 *
 * FW: Firmware
 * Only those MessageTypes are necessary to list in the WelcomeMessage with a type >= 8.
 * The list has to be filled up with 0x00 if less then 4 additional messages are understood.
 *
 */
class CWelcomeMessage: public CCarMessage {
public:

	/*
	 * Constructor which regenerate a message object out of the given byte (char) array.
	 * Note: There can be more than one message in the array. Only the first occurrence is used!
	 * pMessage: contains one or more messages.
	 * iLength: length of the array
	 */
	CWelcomeMessage(alt_u8 *pMessage, int iLength);

	/*
	 * Basic Constructor which initialize the member fields and sets the FW version field
	 * to the given value.
	 */
	CWelcomeMessage(alt_u8 uiVersionCentral);

	/*
	 * Destructor. (Empty implementation)
	 */
	virtual ~CWelcomeMessage();

	void answerMessage(alt_u8 uiVersionComponent, alt_u8 uiComponentType, alt_u8 uiComponentID, alt_u8 *uiOperations);
	void doAction();
	bool getBytes(alt_u8 *pMessage);
	alt_u32 getLength();

	alt_u8 getUiComponentId() const {
		return m_uiComponentID;
	}

	alt_u8 getUiComponentType() const {
		return m_uiComponentType;
	}

	const alt_u8* getUiOperations() const {
		return m_uiOperations;
	}

	alt_u8 getUiVersionCentral() const {
		return m_uiVersionCentral;
	}

	alt_u8 getUiVersionComponent() const {
		return m_uiVersionComponent;
	}

private:
	alt_u8 	m_uiVersionCentral;
	alt_u8 	m_uiVersionComponent;
	alt_u8 	m_uiComponentType;
	alt_u8 	m_uiComponentID;
	alt_u8 	m_uiOperations[4];

	void parseMessage(alt_u8 *pMessage, int iLength);


};

#endif /* WELCOMEMESSAGE_H_ */
