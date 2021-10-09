



#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_
 // X,Y,Z -> Roll,pitch,yaw
 // X,Y,Z -> yaw,Roll,pitch
//------ Private Macros ------------
#define ROLL   2
#define PITCH  3
#define YAW    1

//------- Flags Status ----------
#define ENABLED   1
#define DISABLED  0



//-------- private config ----------
//----- Touch Sensor config ----------
//ST_TouchConfig_t config = {SENSOR_PORT,SENSOR_PIN};
 // {portc,pin0} ------- design rule violation

/*****
 * Description: Get the largest value regardless the signs
 * args: value1 -> (s16_t)
 *		 value2 -> (s16_t)
 *		 value3 -> (s16_t)
 * return: index of the largest value (1 or 2 or 3) -> u8_t
 * Ex: index = App_GetLargestAngle(54,21,100); -> index=3
 */
u8_t App_GetLargestAngle(s16_t value1,s16_t value2,s16_t value3);






#endif