//This header file was generated by ComBuilder on 17.03.2014 17:43:39

/**********************************************************************************
Sensor Description:
GSensor that is build in the DE0-NANO Board.
**********************************************************************************/

#ifndef ACCELERATIONSENSOR_H_
#define ACCELERATIONSENSOR_H_

// Export Interface
#include "alt_types.h"
#include "SensorState.h"

class CAccelerationSensor : public CSensorState
{
public:
    // Constructors
    CAccelerationSensor();

    // Destructors
    virtual ~CAccelerationSensor();

    // Override virtual methods of CSensorState
    virtual CCarMessage *getCarMessage();
    virtual bool updateSensorState(CCarMessage * p_message);

    // TODO: Add getter/setter-methods here

private:
    alt_16 m_iXAcceleraition; // Acceleration in x-direction.
    alt_16 m_iYAcceleration; // Acceleration in y-direction.
    alt_16 m_iZAcceleration; // Acceleration in z-direction.
    bool m_uiAccelerationFlags; // Valid if >= 0.

};

#endif /* ACCELERATIONSENSOR_H_ */