/*
 * Touch.h
 *
 * Created: 10/6/2021 2:47:36 PM
 *  Author: Eslam Emara
 */ 


#ifndef TOUCH_H_
#define TOUCH_H_

#include "../../MCAL/DIO/DIO.h"


typedef struct config{
	EN_PORTS_t TOUCH_PORT;
	EN_PINS_t TOUCH_PIN;
	}ST_TouchConfig_t;
	
/*Initialization function for touch sensor
*inputs: ST_TouchConfig_t configuaration struct in touch.h
*EX :	 ST_TouchConfig_t TouchConfig = {PORTA,PIN0};
		 Touch_Init(TouchConfig);
**/
void Touch_Init(ST_TouchConfig_t config);

/*
*Function to read touch sensor status
*inputs: ST_TouchConfig_t configuaration struct in touch.h
*Return 1 if pressed , 0 otherwise
*
*/
uint8_t Touch_Read(ST_TouchConfig_t config);




#endif /* TOUCH_H_ */