



#ifndef APP_PRIVATE_H_
#define APP_PRIVATE_H_

 // X,Y,Z -> yaw,Roll,pitch
//------ Private Macros ------------

/* Movements of Mouse */
#define UP         0
#define DOWN      1
#define LEFT      2
#define RIGHT       3
#define LEFT_CLICK    4
#define RIGHT_CLICK   5
#define DOUBLE_LEFT_CLICK 6
#define NOTHING     255
#define STOP    8

/* Angles */
#define ROLL   2
#define PITCH  3
#define YAW    1
//------- Flags Status ----------
#define ENABLED   1
#define DISABLED  0


/* Touch Sensor Status */
#define CONTACT     1
#define NOT_CONTACT   0

/* Calibration Status */
#define CALIBRATED    8
#define NOT_CALIBRATED  9

//------ Flags ----------
u8_t RIGHT_CLICK_FLAG = ENABLED;
u8_t LEFT_CLICK_FLAG = ENABLED;
u8_t DL_FLAG = ENABLED;

u16_t cursor_speed = 0;

s16_t reference_angles[3] = {0,0,0};
s16_t current_reading[3] = {0,0,0};
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