/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "MemController.h"

using namespace c2x;

int main()
{
	MemController ctrl = MemController();

	while(1)
	{
		CarState state;

		state = ctrl.getLastElement<CarState>(MemController::AreaId_CarState);

		int speed = state.motorEcus[0].iCurrentSpeed + state.motorEcus[1].iCurrentSpeed + state.motorEcus[2].iCurrentSpeed + state.motorEcus[3].iCurrentSpeed;

		printf("\rSpeed: %+5d mm/s, OpMode: %#x ", speed, state.curMode);

		// TODO: do motor update thingy

		ctrl.pushElement(MemController::AreaId_CarState, state);
	}

	return -1;
}
