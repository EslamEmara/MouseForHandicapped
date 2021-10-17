
#include "App_interface.h"
#include "App_private.h"
#include "App_config.h"


//---- Global Variables ------------------
ST_TouchConfig_t TouchSensor_config = {0x35,0};// {portc,pin0} ------- design rule violation

//----------------------------------------------------
/****
 * Description: Initialization of Different Application components
 * Args: None
 * Return: None
 * Ex: App_Init();
 */
void App_Init()
{
	LED_Init(LED_RED);
	LED_TurnOn(LED_RED);	
	LED_Init(LED_GREEN);
	BNO055_Init();
	Mouse_init();
	Touch_Init(TouchSensor_config);
	while (1){
		if (App_SetReference() == 1){
			break;
		}
	}
}

/****
 * Description: Get mouse Direction from Gradient of head 
 * Args: None
 * Return: u8_t gradient_Direction -> (LEFT, RIGHT, UP, DOWN)
 * Ex: u8_t direction = App_GetImuGradient();
 */
u8_t App_GetImuGradient(void)
{
	s16_t absolute_gradient[3]; // current_reading - reference_point
	//-- get current imu reading
	BNO055_ReadEulerAngles(current_reading);
	//-- compare this reading to calibration point to know imu (head) gradient
	absolute_gradient[0] = current_reading[0] - reference_angles[0];
	if (absolute_gradient[0] < 0 ){
		absolute_gradient[0] +=360;
	}
	absolute_gradient[1] = current_reading[1] - reference_angles[1];
	if (absolute_gradient[1] < 0 ){
		absolute_gradient[1] +=360;
	}
	absolute_gradient[2] = current_reading[2] - reference_angles[2];
	if (absolute_gradient[2] < 0 ){
		absolute_gradient[2] +=360;
	}
	//-- decide depending on calculations to which direction mouse should move
	// get the largest angle of them (sign isn't considered)
	u8_t angle_name = App_GetLargestAngle(absolute_gradient[0],absolute_gradient[1],absolute_gradient[2]);
	
	// change period to set cursor speed
	switch (absolute_gradient[angle_name-1])
	{
		// 20 -> threshold
		case 20 ... 35:
		case 325 ... 340:
		cursor_speed = 1;
		break;
		case 36 ... 50:
		case 310 ... 324:
		cursor_speed = 3;
		break;
		case 51 ... 75: // larger than 60
		case 285 ... 309:
		cursor_speed = 5;
		break;
		case 76 ... 90: // larger than 60
		case 270 ... 284:
		cursor_speed = 7;
		break;
	}
	if (absolute_gradient[angle_name-1] < THRESHOLD || absolute_gradient[angle_name-1] > 360 - THRESHOLD){
		angle_name = STOP;
	}
	// take action on mouse according to angle
	switch(angle_name)
	{
		case STOP:
		//-- no head motion
		RIGHT_CLICK_FLAG = ENABLED;
		LEFT_CLICK_FLAG = ENABLED;
		DL_FLAG = ENABLED;
		return NOTHING;
		break;
		// head is turned around X-axis (RIGHT_CLICK, LEFT_CLICK, DOUBLE_LEFT_CLICK)
		case ROLL:
		// angle > threshold?
		// angle range [20:180]
		if(absolute_gradient[angle_name-1] >= THRESHOLD && absolute_gradient[angle_name-1] < 180 && RIGHT_CLICK_FLAG)
		{
			// disable flag to stop sending this signal multiple times
			RIGHT_CLICK_FLAG = DISABLED;
			// enable left click
			LEFT_CLICK_FLAG = ENABLED;
			// enable double left flag
			DL_FLAG = ENABLED;
			return RIGHT_CLICK;
			
		}
		
		// angle in range [320:360] -> left click
		else if ((absolute_gradient[angle_name-1] > 360-(THRESHOLD+40)) && (absolute_gradient[angle_name-1] < 360 - THRESHOLD) && LEFT_CLICK_FLAG)
		{
			// enable right click
			RIGHT_CLICK_FLAG = ENABLED;
			// disable flag to stop sending this signal multiple times
			LEFT_CLICK_FLAG = DISABLED;
			// enable double left flag
			DL_FLAG = ENABLED;
			return LEFT_CLICK;
		}
		// angle in range [180:320] -> double left click
		else if((absolute_gradient[angle_name-1] > 180) && (absolute_gradient[angle_name-1] < 300) && DL_FLAG )
		{
			DL_FLAG = DISABLED;
			LEFT_CLICK_FLAG = DISABLED;
			RIGHT_CLICK_FLAG = ENABLED;
			return DOUBLE_LEFT_CLICK;
		}
		return NOTHING;
		break;
		// head is turned around Y-axis (UP, DOWN)
		case PITCH:
		// enable flags so the signal can be sent again
		// angle range [20:180]
		if(absolute_gradient[angle_name-1] >= THRESHOLD && absolute_gradient[angle_name-1] < 180)
		{ RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return UP; }
		// angle range [180:360]
		else if ( absolute_gradient[angle_name-1] > 180 && absolute_gradient[angle_name-1] < (360 - THRESHOLD) )
		{ RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return DOWN; }
		return NOTHING;
		break;
		// head is turned around Z-axis (Left, Right)
		case YAW:
		// enable flags so the signal can be sent again
		if(absolute_gradient[angle_name-1] >= THRESHOLD && absolute_gradient[angle_name-1] < 180)
		{RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return RIGHT; }
		else if ( absolute_gradient[angle_name-1] > 180 && absolute_gradient[angle_name-1] < (360 - THRESHOLD) )
		{RIGHT_CLICK_FLAG = ENABLED; LEFT_CLICK_FLAG = ENABLED; DL_FLAG = ENABLED; return LEFT; }
		return NOTHING;
		break;

	}
	//-- no head motion
	return NOTHING;
}


/****
 * Description: order Mouse to do a certain action
 * Args: order (LEFT, RIGHT, UP, DOWN, LEFT_CLICK, RIGHT_CLICK) -> see App_config.h
 * Return: None
 * Ex: App_MoveMouse(LEFT_CLICK);
 */				
void App_OrderMouse(u8_t order)
{
	switch(order)
	{
		case LEFT:			Mouse_MoveLeft  ();		break;
		case RIGHT:			Mouse_MoveRight ();		break;
		case UP:			Mouse_MoveUp    ();		break;
		case DOWN:			Mouse_MoveDown  ();		break;
		case LEFT_CLICK:	Mouse_LeftClick ();		break;
		case RIGHT_CLICK:	Mouse_RightClick();		break;
		case DOUBLE_LEFT_CLICK:
							Mouse_LeftClick();
							Delay_ms_independent(1);
							Mouse_LeftClick();
							break;
		case NOTHING:		/* do nothing */		break;
	}
}

//--------------------------------

u8_t App_SetReference(){
	if (App_GetTouchSensorState() == CONTACT){
		Delay_ms_independent(2000);
		if (App_GetTouchSensorState() == CONTACT){
			BNO055_ReadEulerAngles(reference_angles);       // -100 , -50 , 0
			return 1;
		}
	}
	return 0;
}

//----------------------------------

/****
 * Description: Get the status of touch sensor -> contact on the head or not
 * Args: None
 * Return: u8_t state (CONTACT, NOT_CONTACT)
 * Ex: u8_t state = App_GetTouchSensorState();
 */
u8_t App_GetTouchSensorState(void)
{
	/* get sensor reading */
	u8_t reading = Touch_Read(TouchSensor_config);	
	if(reading == HIGH)
	{
		LED_TurnOn(LED_GREEN);
		LED_TurnOff(LED_RED);
		return CONTACT;
	}
	else
	{
		LED_TurnOff(LED_GREEN);
		LED_TurnOn(LED_RED);
		return NOT_CONTACT;
	}
}


/****
 * Description: Get initial point that the others are measured relative to (calibration point)
 * Args: array of 3 elements[x,y,z] (float*)
 * Return: None
 * Ex: App_GetImuCalibPoint(reference_angles);
 */
void App_GetImuCalibPoint(void)
{
	BNO055_ReadEulerAngles(reference_angles);
}



/****
 * Description: check if sensors are calibrated successfully or not
 * Args: None
 * Return: calibration status [CALIBRATED, NOT_CALIBRATED] -> (u8_t)
 * Ex: u8_t calib_status = App_GetCalibStatus();
 */
u8_t App_GetCalibStatus(void)
{
	u8_t sensor_S = BNO055_GetCalibStat(SYSTEM);
	u8_t sensor_G = BNO055_GetCalibStat(GYROSCOPE);
	u8_t sensor_A = BNO055_GetCalibStat(ACCELOMETER);
	u8_t sensor_M = BNO055_GetCalibStat(MAGNETOMETER);
	
	if( sensor_S>LOW_CALIBRATED && sensor_G>LOW_CALIBRATED && sensor_A>LOW_CALIBRATED && sensor_M>LOW_CALIBRATED )
	{
		return CALIBRATED;
	}
	return NOT_CALIBRATED;
}



/*****
 * Description: Get the largest value regardless the signs
 * args: value1 -> (s16_t)
 *		 value2 -> (s16_t)
 *		 value3 -> (s16_t)
 * return: index of the largest value (1 or 2 or 3) -> u8_t
 * Ex: index = App_GetLargestAngle(54,21,100); -> index=3
 */
u8_t App_GetLargestAngle(s16_t value1,s16_t value2,s16_t value3)
{ // yaw roll pitch
	
	if (value1 > 180) value1-=360;
	if (value2 > 180) value2-=360;
	if (value3 > 180) value3-=360;
	
	value1 = abs(value1);
	value2 = abs(value2);
	value3 = abs(value3);
	
	if(value1 > value2)
	{
		if(value1 > value3)   { return 1; }
		else          { return 3; }
	}
	else
	{
		if(value2 > value3)   { return 2; }
		else          { return 3; }
	}
}