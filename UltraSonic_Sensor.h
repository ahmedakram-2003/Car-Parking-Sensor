/*
 * UltraSonic_Sensor.h
 *
 *  Created on: Oct 3, 2025
 *      Author: Akram
 */

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include"std_types.h"
#include"gpio.h"


#define UltraSonic_PORT_ID         PORTD_ID
#define UltraSonic_ECHO_PIN_ID     PIN6_ID
#define UltraSonic_TRIGGER_PIN_ID  PIN7_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialize the Ultrasonic driver:
 *  - Initialize ICU driver
 *  - Set ICU callback
 *  - Configure Trigger pin as output
 */
void Ultrasonic_init(void);


/*
 * Description :
 * Send the trigger pulse to the Ultrasonic sensor
 */
void Ultrasonic_Trigger(void);


/*
 * Description :
 * Measure the distance using Ultrasonic sensor
 * Returns: distance in cm
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description :
 * ICU Callback function
 *  - Called on Rising/Falling edges
 *  - Calculates the high time of the Echo pulse
 */
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_SENSOR_H_ */
