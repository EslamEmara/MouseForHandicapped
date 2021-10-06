



#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

//------ Private Macros ------------
#define ROLL  1
#define PITCH 2
#define YAW   3

//-------- private config ----------
//----- Touch Sensor config ----------
//ST_TouchConfig_t config = {SENSOR_PORT,SENSOR_PIN};
ST_TouchConfig_t config = {0x35,0}; // {portc,pin0} ------- design role violation

/*****
 * Description: Get the largest value regardless the signs
 * args: value1 -> (sint16_t)
 *		 value2 -> (sint16_t)
 *		 value3 -> (sint16_t)
 * return: index of the largest value (1 or 2 or 3) -> uint8_t
 * Ex: index = App_GetLargestAngle(54,21,100); -> index=3
 */
static uint8_t App_GetLargestAngle(sint16_t value1,sint16_t value2,sint16_t value3);






#endif