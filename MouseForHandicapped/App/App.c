

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
	BNO055_Init();
	Mouse_init();
	TouchInit();
}

/****
 * Description: Get Direction of Gradient of head
 * Args: None
 * Return: uint8_t gradient Direction (LEFT, RIGHT, UP, DOWN)
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
		return CONTACT;
	}
	else
	{
		return NOT_CONTACT;
	}
}










