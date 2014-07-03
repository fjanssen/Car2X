/*
 * motor_pwm.cpp
 *
 *  Created on: 11.11.2013
 *      Author: Florian
 */

#include "motor_pwm.h"
#include <stdio.h>
#include <sys/time.h>



void motor_setting(unsigned long phase1, unsigned long duty1,unsigned long phase2, unsigned long duty2,
		unsigned long period,unsigned long enable)
{
	volatile unsigned int * pwm_en		=(volatile unsigned int *)	PWM_EN;
	volatile unsigned int * pwm_period	=(volatile unsigned int *)	PWM_PERIOD;
	volatile unsigned int * pwm_phase1	=(volatile unsigned int *)	PWM_PHASE1;
	volatile unsigned int * pwm_phase2	=(volatile unsigned int *)	PWM_PHASE2;
	volatile unsigned int * pwm_duty1	=(volatile unsigned int *)	PWM_DUTY1;
	volatile unsigned int * pwm_duty2	=(volatile unsigned int *)	PWM_DUTY2;

	// Check for invalid parameters
	if(enable > 2)
		enable = 0;

	if(duty1 > 100000)
		duty1 = 100000;

	if(duty2 > 100000)
		duty2 = 100000;

	// Write settings to PWM-generator
	* pwm_en		= enable;
	* pwm_period	= period;
	* pwm_phase1	= phase1;
	* pwm_phase2	= phase2;
	* pwm_duty1		= duty1;
	* pwm_duty2		= duty2;

}

void setSpeed(alt_32 uiSpeed)
{
	if(uiSpeed > 0)
	{
		motor_setting(0,uiSpeed,0,0,100000,1);
	}
	else
	{
		motor_setting(0,0,0,-1 * uiSpeed,100000,2);
	}

}

alt_32 measureSpeed(void)
{
	volatile alt_u32 * pEnc = (volatile alt_u32 *) (0x80000000 | MOTOR_ENCODER_0_BASE);
	volatile alt_u32 * pDir = (volatile alt_u32 *) (0x80000000 | MOTOR_ENCODER_0_BASE + 4);
	volatile alt_u32 current_speed;

	*pEnc =  1;
	delay(10);
	current_speed = *pEnc;



	current_speed *= 100;
	current_speed *= WHEEL_SCALE;
	current_speed /= 4288;

	if(*pDir == INVERTED)
		return current_speed;
	else
		return current_speed * -1;
}

alt_32 measureSpeedUnblocking(void)
{
	volatile alt_u32 * pEnc = (volatile alt_u32 *) (0x80000000 | MOTOR_ENCODER_0_BASE);
	volatile alt_u32 * pDir = (volatile alt_u32 *) (0x80000000 | MOTOR_ENCODER_0_BASE + 4);
	volatile alt_u32 pDirOld;
	volatile alt_u32 current_speed;

	// NOTE: Call every 10 ms!!!!
	current_speed = *pEnc;
	pDirOld = *pDir;
	*pEnc =  1;

	current_speed *= 100;
	current_speed *= WHEEL_SCALE;
	current_speed /= 4288;

	if(pDirOld == INVERTED)
		return current_speed;
	else
		return current_speed * -1;
}


