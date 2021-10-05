
#include "../ECUAL/LED/LED.h"
#include "../ECUAL/BNO055/BNO055.h"
#include "../ECUAL/Mouse/Mouse.h"


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
	TouchInit();
}

/****
 * Description: Get Direction of Gradient of head
 * Args: None
 * Return: uint8_t gradient Direction (LEFT, RIGHT, UP, DOWN, LEFT_CLICK, RIGHT_CLICK)
 * Ex: uint8_t direction = App_GetImuGradDirection();
 */				
uint8_t App_GetImuGradDirection(void)
{
	
}


/****
 * Description: order Mouse to do a certain action
 * Args: order (LEFT, RIGHT, UP, DOWN, LEFT_CLICK, RIGHT_CLICK) -> see App_config.h
 * Return: None
 * Ex: App_MoveMouse(LEFT_CLICK);
 */				
void App_OrderMouse(uint8_t order)
{
	switch(order)
	{
		case LEFT:			Mouse_MoveLeft  ();		break;
		case RIGHT:			Mouse_MoveRight ();		break;
		case UP:			Mouse_MoveUP    ();		break;
		case DOWN:			Mouse_MoveDown  ();		break;
		case LEFT_CLICK:	Mouse_LeftClick ();		break;
		case RIGHT_CLICK:	Mouse_RightClick();		break;
		default:  									break;
	}
}

/****
 * Description: Get the status of touch sensor -> contact on the head or not
 * Args: None
 * Return: uint8_t state (CONTACT, NOT_CONTACT)
 * Ex: uint8_t state = App_GetTouchSensorState();
 */				
 
uint8_t App_GetTouchSensorState(void)
{
	/* get sensor reading */
	uint8_t reading = GetTouchReading();	
	if(reading == HIGH)
	{
		LED_TurnOn(LED_GREEN);
		LED_TurnOff(LED_RED);
		return CONTACT;
	}
	else
	{
		LED_TurnOn(LED_RED);
		LED_TurnOff(LED_GREEN);
		return NOT_CONTACT;
	}
}


/****
 * Description: Get initial point that the others are measured relative to (calibration point)
 * Args: array of 3 elements[x,y,z] (float*)
 * Return: None
 * Ex: App_GetImuCalibPoint(angles);
 */
void App_GetImuCalibPoint(float angles[])
{
	// get calibration point
}



/****
 * Description: check if sensors are calibrated successfully or not
 * Args: None
 * Return: calibration status [CALIBRATED, NOT_CALIBRATED] -> (uint8_t)
 * Ex: uint8_t calib_status = App_GetCalibStatus();
 */
uint8_t App_GetCalibStatus(void)
{
	uint8_t sensor_S = BNO055_GetCalibStat(SYSTEM);
	uint8_t sensor_G = BNO055_GetCalibStat(GYROSCOPE);
	uint8_t sensor_A = BNO055_GetCalibStat(ACCELOMETER);
	uint8_t sensor_M = BNO055_GetCalibStat(MAGNETOMETER);
	
	if( sensor_S>LOW_CALIBRATED && sensor_G>LOW_CALIBRATED && sensor_A>LOW_CALIBRATED && sensor_M>LOW_CALIBRATED )
	{
		return CALIBRATED
	}
	return NOT_CALIBRATED
}








