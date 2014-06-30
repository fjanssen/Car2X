/*
 * main.h
 *
 *  Created on: 24.01.2014
 *      Author: Florian
 */

#ifndef SENSORSTATE_H_
#define SENSORSTATE_H_

#include "alt_types.h"
#include "CarMessage.h"

/*
 * This class is the endpoint of sensor communication. The chain looks like:
 * 1. SensorState generates request message
 * 2. CarAPI collects all request messages and packs them into a CarProtocol packet
 * 3. This packet is sended to the motor-ECUs
 * 4. Every message is answered and filled with sensor values
 * 5. The answer packet is send back
 * 6. CarAPI splitts the received answer into single messages
 * 7. The SensorState gets his personal answer message 
 * 8. The SensorState reads out the fields of the answer and represents the 
 *    data in a more useful way.
 * 9. Next step will be 1. again.
 *
 * Doing so give the possibility to seperate network communication from logic 
 * (path) planning. The (AI) agent can ask the SensorState about the current
 * sensor state and need no information about networking, ...
 *
 * This class contains only the basic fields an methods for such a SensorState. Only
 * subclasses can handle the variety of sensors and messages!
 */
class CSensorState
{
public:
    /*
	 * Constructs a new SensorState and initialize the access mutex.
	 */
	CSensorState();
	
	/*
	 * Empty destuctor.
	 */
	virtual ~CSensorState();

	/*
	 * Generates a new request message which will be send to the motor-ECU.
	 * The subclasses must implement this method and return their Message type.
	 * The basic implementation in this super class returns 0.
	 */ 
	virtual CCarMessage *getCarMessage();
	
	/*
	 * The SensorState is updated with an actual message. The real message type
	 * depends on the subclasses.
	 * The subclasses must implement this method!
	 */
	virtual bool updateSensorState(CCarMessage * p_message);

	/*
	 * Returns the message type which is used in getCarMessage() and updateSensorState(..).
	 * The subclasses must implement this method!
	 */
	alt_u8 getType();
	
	/*
	 * Are the sensor fields valid?
	 */ 
	bool isValid();


protected:
	alt_u8	m_uiType;		// corresponding message type
	bool    m_bStateValid;
};


#endif /* SENSORSTATE_H_ */
