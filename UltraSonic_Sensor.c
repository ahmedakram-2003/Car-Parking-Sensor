/*
 * UltraSonic_Sensor.c
 *
 *  Created on: Oct 3, 2025
 *      Author: Akram
 */
#include"icu.h"
#include"UltraSonic_Sensor.h"
#include<avr/io.h>
#include<util/delay.h>


uint8 echo_edgecount = 0 ;
uint16  Timer_Value  = 0 ;


void Ultrasonic_init(void){
	ICU_ConfigType ICU_UltraSonic_Configurations = {F_CPU_8,RAISING};
	ICU_init(&ICU_UltraSonic_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	SREG |=(1<<7);

	GPIO_setupPinDirection(UltraSonic_PORT_ID ,UltraSonic_TRIGGER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(UltraSonic_PORT_ID ,UltraSonic_TRIGGER_PIN_ID,LOGIC_LOW);
}
void Ultrasonic_Trigger(void){

	GPIO_writePin(UltraSonic_PORT_ID ,UltraSonic_TRIGGER_PIN_ID,LOGIC_HIGH);

	_delay_us(10);

	GPIO_writePin(UltraSonic_PORT_ID ,UltraSonic_TRIGGER_PIN_ID,LOGIC_LOW);

}
uint16 Ultrasonic_readDistance(void){
	uint16 distance;
	Ultrasonic_Trigger();
	distance = ((Timer_Value*0.0085)+1);
	return distance ;
}

void Ultrasonic_edgeProcessing(void){
	 echo_edgecount++;

	 if(echo_edgecount == 1){
		 ICU_clearTimerValue();
		 ICU_setEdgeDetectionType(FALLING);
	 }

	 else if (echo_edgecount == 2)
	 {
		 /* Set the time value in the global variable to use it in distance calculations */
		 Timer_Value = ICU_getInputCaptureValue();

		 /* Set the next measurement edge type  */
		 ICU_setEdgeDetectionType(RAISING);
		 echo_edgecount = 0;
	 }

}

