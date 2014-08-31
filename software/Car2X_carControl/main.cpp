/*********************************************************************
 *
 * Car Control Core
 * 
 * \brief The Car Control Core is the figurative center of the car.
 *        All the data from various parts and components are brought
 *        together here, and the final decision how to control the
 *        car motors is made.
 * 
 * \author Johannes <jwindelen@gmail.com>
 * 
 *********************************************************************/

/* ===================================================================
 * Includes
 * ==================================================================*/
#include "MemController.h"
#include "ErrHandler.h"
#include <cstdlib>
#include <string.h>
#include "nios2.h"

/* ===================================================================
 * Local prototypes
 * ==================================================================*/
/* -------------------------------------------------------------------
 * \name  switchMode
 * \brief handles the operating mode transitions. The current and 
 *        requested states are found in the CarState function parameter
 * 
 * \param[out] state: the current car state. Modifies the currOpMode
 *                 member variable
 * ------------------------------------------------------------------*/
static void switchMode(CarState * state);

/* -------------------------------------------------------------------
 * \name setMotorSpeeds
 * 
 * \brief calculates the motor speeds according to the requested 
 *        velocities and the limits imposed by the current operating 
 *        mode.
 * 
 * \param[out] state: the current car state. Modifies the MotorECU_State
 *                 member variable.
 * ------------------------------------------------------------------*/
static void setMotorSpeeds(CarState * state);


/* ===================================================================
 * Implementation
 * ==================================================================*/
/* -------------------------------------------------------------------
 * main
 * ------------------------------------------------------------------*/
int main() {
    // Get a memory controller to access the CarState in the shared memory
    MemController<CarState> ctrl = MemController<CarState>();
  
	CarState state;

    // initialise state. Zero out the first element. Yes, we might lose
    // some data in the unlikely event that the commCore starts up before
    // the car Control one. But since the shared memory isn't initialised
    // after a soft-reset, this avoids working with a corrupt state.

    // A better solution would be to initialise the shared memory in the
    // MemController Constructor, by adding an isInitialised flag to the
    // SharedMemory.
	state = ctrl.get(true);
	memset(&state,0,sizeof(state));
	ctrl.push(state);

    // The main loop.
	while(true)
	{
        // Add a delay so the control core doesn't hog the shared memory
        // mutex
        int i;
		for(i = 0; i < 500000; i++){;}

		// get the lastest car state from the shared memory
		state = ctrl.get(true);

		// print some diagnostics information
		int speed = state.motorEcus[0].iCurrentSpeed + 
            state.motorEcus[1].iCurrentSpeed + 
            state.motorEcus[2].iCurrentSpeed + 
            state.motorEcus[3].iCurrentSpeed;
		LOG_DEBUG("\rSpeed: %+5d mm/s, OpMode: %#x ", speed, state.currMode);

		// perform state switch if requested.
		if(state.reqMode != state.currMode)
		{
			switchMode(&state);
		}

        // keep track of which states we have processed in the control core
		state.counterCarControl=state.counterComm;

        // calculate and set the 4 motor speeds
		setMotorSpeeds(&state);

		ctrl.push(state);
	}

	return -1;
}

/* -------------------------------------------------------------------
 * switchMode
 * ------------------------------------------------------------------*/
void switchMode(CarState * state)
{
	LOG_DEBUG("Switching operating mode: %d -> %d", state->currMode, state->reqMode);

	switch(state->reqMode)
	{
	case OPMODE_PREOPERATIONAL:
    {
        state->iMaxSpeed = OPMODE_IDLE_MAXSPEED;
        break;
    }
	case OPMODE_IDLE:
	{
		state->iMaxSpeed = OPMODE_IDLE_MAXSPEED;
		break;
	}
	case OPMODE_EMERGENCYSTOP:
	{
		state->iMaxSpeed = OPMODE_EMERGENCYSTOP_MAXSPEED;
		break;
	}
	case OPMODE_AUTODRIVE:
	{
		state->iMaxSpeed = OPMODE_AUTODRIVE_MAXSPEED;
        // set the controlling IP address to the image processor
        state->ip1 = VCIPPart1;
        state->ip2 = VCIPPart2;
        state->ip3 = VCIPPart3;
        state->ip4 = VCIPPart4;

		break;
	}
	case OPMODE_MANUDRIVE:
	{
		state->iMaxSpeed = OPMODE_MANUDRIVE_MAXSPEED;
        // set the controlling IP address to that which requested
        // the manual drive
        state->ip1 = state->reqip1;
		state->ip2 = state->reqip2;
		state->ip3 = state->reqip3;
		state->ip4 = state->reqip4;
		break;
	}
	default:
	{
		LOG_ERROR(ERR_CARCTRL_INVALID_MODE, "Requested opMode: %d", state->reqMode);
		break;
	}
	}

	state->currMode = state->reqMode;
}

/* -------------------------------------------------------------------
 * setMotorSpeeds
 * ------------------------------------------------------------------*/
void setMotorSpeeds(CarState * state)
{
	int iCurrVel, iReqVel; // velocity in mm/s
	alt_u16 fVelFactor; // fixed comma integer, with resolution of 0.01

	// Log current state:
	iCurrVel = (state->motorEcus[0].iCurrentSpeed
                + state->motorEcus[1].iCurrentSpeed
                + state->motorEcus[2].iCurrentSpeed
                + state->motorEcus[3].iCurrentSpeed) / 4;

	LOG_DEBUG("Current velocity: %+5d, LF: %+3hd, LR: %+3hd, RF: %+3hd, RR: %+3hd",
              iCurrVel, state->motorEcus[0].iCurrentSpeed, state->motorEcus[1].iCurrentSpeed,
              state->motorEcus[2].iCurrentSpeed, state->motorEcus[3].iCurrentSpeed);

	//LOG current PIController values
	LOG_DEBUG("LF: %hd, %hd, %hd LR: %hd, %hd, %hd RF: %hd, %hd, %hd RR: %hd, %hd, %hd", 
              state->motorEcus[0].iIType, 
              state->motorEcus[0].iPType,
              state->motorEcus[0].iMaxSpeed,
              state->motorEcus[1].iIType,
              state->motorEcus[1].iPType,
              state->motorEcus[1].iMaxSpeed,
              state->motorEcus[2].iIType,
              state->motorEcus[2].iPType,
              state->motorEcus[2].iMaxSpeed,
              state->motorEcus[3].iIType,
              state->motorEcus[3].iPType,
              state->motorEcus[3].iMaxSpeed);

	// Calculate individual wheel speeds
	iReqVel = (state->reqVelocity.iFrontLeft
               + state->reqVelocity.iFrontRight
               + state->reqVelocity.iRearLeft
               + state->reqVelocity.iRearRight) / 4;

	LOG_DEBUG("Request velocity: %+5hd, LF: %+3hd, LR: %+3hd, RF: %+3hd, RR: %+3hd",
              iReqVel, 
              state->reqVelocity.iFrontLeft, state->reqVelocity.iRearLeft,
              state->reqVelocity.iFrontRight, state->reqVelocity.iRearRight);

	if(abs(iReqVel) > abs(state->iMaxSpeed))
	{
		fVelFactor = state->iMaxSpeed * 100 / iReqVel;
		LOG_DEBUG("Request velocity too high. OpMode: %hd, MaxVel: %hd, VelFactor: %f",
                  state->currMode, state->iMaxSpeed, fVelFactor);
	}
	else
	{
		fVelFactor = 100;
	}

	// Update state:
	state->motorEcus[0].iDesiredSpeed = (alt_16) (state->reqVelocity.iFrontLeft  * fVelFactor / 100);
	state->motorEcus[1].iDesiredSpeed = (alt_16) (state->reqVelocity.iRearLeft * fVelFactor / 100);
	state->motorEcus[2].iDesiredSpeed = (alt_16) (state->reqVelocity.iFrontRight   * fVelFactor / 100);
	state->motorEcus[3].iDesiredSpeed = (alt_16) (state->reqVelocity.iRearRight  * fVelFactor / 100);

    // TODO: ultrasonic sensor data. We do not currently have these
    //       setup in hardware & have not setup the comm core to
    //       process the messages
}
