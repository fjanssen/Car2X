#ifndef MOTOR_PWM_H_
#define MOTOR_PWM_H_

#include <system.h>
#include <alt_types.h>

#include "..\etc\utility.h"
#include "..\properties.h"

// Define Address for PWM-generator
#define PWM_EN (0x80000000 | A_2_CHANNEL_PWM_0_BASE)
#define PWM_PERIOD PWM_EN+1
#define PWM_DUTY1 PWM_EN+2
#define PWM_DUTY2 PWM_EN+3
#define PWM_PHASE1 PWM_EN+4
#define PWM_PHASE2 PWM_EN+5

/*
 * Sets the motor PWM attributes direct. The used PWM consists of two channels which is required to drive
 * into both directions.
 * phase1: Phase of the first channel.
 * duty1: Duty-cycle in 0.01% (100000 means full speed in direction 1)
 * phase2: see above
 * duty2: see above
 * period: Period of the PWM
 * enable: 0 -> stop, 1 -> direction 1, 2 -> direction 2, others -> must not be used!
 *
 * Note: Please use the setSpeed(..) function!
 */
void motor_setting(unsigned long phase1, unsigned long duty1,unsigned long phase2, unsigned long duty2,
		unsigned long period,unsigned long enable);

/*
 * Is the given speed positive the wheel turns in direction 1, otherwise in direction 2.
 */
void setSpeed(alt_32 uiSpeed);

/*
 * Counts the ticks of the hall-sensor from the last call of this function on. This function has
 * to be called EVERY 10 ms.
 * The returned speed is positive if the wheel turns in direction 1, otherwise negative.
 * The speed is in mm/sec. For this conversion the WHEEL_SCALE is needed.
 */
alt_32 measureSpeedUnblocking(void);

/*
 * Counts the ticks of the hall-sensor over 10 ms. The returned speed is positive if the wheel
 * turns in direction 1, otherwise negative.
 * The speed is in mm/sec. For this conversion the WHEEL_SCALE is needed.
 */
alt_32 measureSpeed(void);

#endif // MOTOR_PWM_H_
