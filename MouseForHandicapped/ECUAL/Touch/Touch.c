/*
 * Touch.c
 *
 * Created: 10/6/2021 2:47:22 PM
 *  Author: Eslam Emara
 */ 
#include "Touch.h"

/*Initialization function for touch sensor
*inputs: ST_TouchConfig_t configuaration struct in touch.h
*EX :	 ST_TouchConfig_t TouchConfig = {PORTA,PIN0};
		 Touch_Init(TouchConfig);
**/
void Touch_Init(ST_TouchConfig_t config){
	DIO_setPinDir(config.TOUCH_PORT,config.TOUCH_PIN,IN);
}

/*
*Function to read touch sensor status
*inputs: ST_TouchConfig_t configuaration struct in touch.h
*Return 1 if pressed , 0 otherwise
*
*/
uint8_t Touch_Read(ST_TouchConfig_t config){
	return DIO_getPin(config.TOUCH_PORT,config.TOUCH_PIN);
}