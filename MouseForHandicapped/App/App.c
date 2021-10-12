
#include "App_interface.h"


//---- Global Variables ------------------
ST_TouchConfig_t TouchSensor_config = {0x35,0};// {portc,pin0} ------- design rule violation
//------ Flags ----------
u8_t RIGHT_CLICK_FLAG = ENABLED;
u8_t LEFT_CLICK_FLAG = ENABLED;
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
}

/****
 * Description: Get mouse Direction from Gradient of head 
 * Args: None
 * Return: u8_t gradient_Direction -> (LEFT, RIGHT, UP, DOWN)
 * Ex: u8_t direction = App_GetImuGradient();
 */				
u8_t App_GetImuGradient(void)
{
	static u16_t period = 1000; // to control cursor speed with
	
	// define cursor speed
	Delay_ms_independent(period);
	s16_t absolute_gradient[3]; // current_reading - reference_point
	//-- get current imu reading
	BNO055_ReadEulerAngles(current_reading);
	//-- compare this reading to calibration point to know imu (head) gradient
	absolute_gradient[0] = current_reading[0] - reference_angles[0]; // YAW
	absolute_gradient[1] = current_reading[1] - reference_angles[1]; // ROLL
	absolute_gradient[2] = current_reading[2] - reference_angles[2]; // PITCH
	//-- decide depending on calculations to which direction mouse should move
	// get the largest angle of them (sign isn't considered)
	u8_t angle_name = App_GetLargestAngle(absolute_gradient[0],absolute_gradient[1],absolute_gradient[2]);
	
	// change period to set cursor speed 
	switch (absolute_gradient[angle_name-1])
	{
		// 10 -> threshold
		case 10 ... 20:
			period = 1000;
			break;
		case 21 ... 35:
			period = 400;
			break;
		default: // larger than 60
			period = 0;
			break;
	}
	
	// take action on mouse according to angle
	switch(angle_name)
	{
		// head is turned around X-axis
		case ROLL:
			// positive angle > threshold?
			if(absolute_gradient[angle_name-1] >= THRESHOLD_X && RIGHT_CLICK_FLAG)
			{ 
				// disable flag to stop sending this signal multiple times
				RIGHT_CLICK_FLAG = DISABLED;
				// small angle (<25) -> single right click
				if (absolute_gradient[angle_name] < 25)
				{
					return RIGHT_CLICK;
				}
				// larger angle -> double right click
				 return DOUBLE_RIGHT_CLICK;
			}
			// negative angle > threshold?
			else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_X && LEFT_CLICK_FLAG)
			{
				// disable flag to stop sending this signal multiple times
				 LEFT_CLICK_FLAG = DISABLED;
				 return LEFT_CLICK; 
			}
			break;
		// head is turned around Y-axis
		case PITCH:
		// enable flags so the signal can be sent again
			if(absolute_gradient[angle_name-1] >= THRESHOLD_Y){ RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return UP; }
			else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_Y ){ RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return DOWN; }
			break;
		// head is turned around Z-axis
		case YAW:
		// enable flags so the signal can be sent again
			if(absolute_gradient[angle_name-1] >= THRESHOLD_Z){RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return RIGHT; }
			else if ( (-1*absolute_gradient[angle_name-1]) >= THRESHOLD_Z ){RIGHT_CLICK_FLAG = ENABLED; RIGHT_CLICK_FLAG = ENABLED; return LEFT; }
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
		case DOUBLE_RIGHT_CLICK:
							Mouse_RightClick();
							Delay_ms_independent(1);
							Mouse_RightClick();
							break;
		case NOTHING:		/* do nothing */		break;
	}
}

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
	value1 = abs(value1);
	value2 = abs(value2);
	value3 = abs(value3);
	if(value1 > value2)
	{
		if(value1 > value3)		{ return 1; }
		else 					{ return 3; }
	}
	else
	{
		if(value2 > value3)		{ return 2; }
		else 					{ return 3; }
	}
}