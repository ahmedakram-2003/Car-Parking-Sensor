/*
 * MiniProject4_CarParkingSensor.c
 *
 *  Created on: Oct 3, 2025
 *      Author: Akram
 */

#include "std_types.h"
#include "UltraSonic_Sensor.h"
#include "lcd.h"
#include "BUZZER.h"
#include "led.h"
#include <util/delay.h>

int main(void)
{
	/* enable all modules using init functions*/
	LCD_init();
	Ultrasonic_init();
	LEDS_init();
	Buzzer_init();

	uint8 distance = 0;

	while(1)
	{
		/* Measure the distance */
		distance = Ultrasonic_readDistance();

		/* Fix startup bug in ultrasonic  */
		while(distance == 1)
		{
			distance = Ultrasonic_readDistance();
		}

		/* Display distance on LCD */
		LCD_displayStringRowColumn(0,0,"Distance = ");
		LCD_moveCursor(0,11);
		LCD_intgerToString(distance);

		/* Clear extra digits if number < 100 */
		if(distance < 100){
			LCD_displayCharacter(' ');

		LCD_displayString("cm ");
		}
		/* LEDs and Buzzer control*/
		if(distance > 20)
		{
			LED_off(RED_LED);
			LED_off(GREEN_LED);
			LED_off(BLUE_LED);
			Buzzer_off();
			LCD_displayStringRowColumn(1,5,"     ");
		}
		else if(distance > 15 && distance <= 20)
		{
			LED_on(RED_LED);
			LED_off(GREEN_LED);
			LED_off(BLUE_LED);
			Buzzer_off();
			LCD_displayStringRowColumn(1,5,"     ");
		}
		else if(distance > 10 &&  distance <= 15)
		{
			LED_on(RED_LED );
			LED_on(GREEN_LED);
			LED_off(BLUE_LED);
			Buzzer_off();
			LCD_displayStringRowColumn(1,5,"     ");
		}
		else if(distance > 5 && distance <= 10)
		{
			LED_on(RED_LED);
			LED_on(GREEN_LED);
			LED_on(BLUE_LED);
			Buzzer_off();
			LCD_displayStringRowColumn(1,5,"     ");
		}
		else
		{
			while(distance <= 5)
			{
				LCD_displayStringRowColumn(0,0,"Distance = ");
				LCD_moveCursor(0,11);
				LCD_intgerToString(distance);
				/* Update distance continuously */
				distance = Ultrasonic_readDistance();

				/* Flash LEDs & Buzzer */
				LED_on(RED_LED);
				LED_on(GREEN_LED);
				LED_on(BLUE_LED);
				Buzzer_on();
				_delay_ms(200);

				LED_off(RED_LED);
				LED_off(GREEN_LED);
				LED_off(BLUE_LED);
				Buzzer_off();
				_delay_ms(200);

				/* displaying stop message */
				LCD_displayStringRowColumn(1,5,"STOP ");
			}
		}
	}
}
