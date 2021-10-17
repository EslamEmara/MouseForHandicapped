


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

#include <stdlib.h>
#include "../MCAL/DIO/TypeDefs.h"
#include "../ECUAL/LED/LED_interface.h"
#include "../ECUAL/Touch/Touch.h"
#include "../ECUAL/BNO055/BNO055.h"
#include "../ECUAL/Mouse/Mouse.h"
#include "../ECUAL/Delay/Delay_interface.h"



//------ Global Variables --------
 // X,Y,Z -> Roll,pitch,yaw
 // X,Y,Z -> yaw,Roll,pitch
//s16_t reference_angles[3];
//s16_t current_reading[3];
//
//
//
///* Movements of Mouse */
//#define UP   	 		0
//#define DOWN 	 		1
//#define LEFT 	 		2
//#define RIGHT    		3
//#define LEFT_CLICK		4
//#define RIGHT_CLICK		5
//#define DOUBLE_RIGHT_CLICK  6
//#define NOTHING			255
//
///* Touch Sensor Status */
//#define CONTACT			1
//#define NOT_CONTACT		0
//
///* Calibration Status */
//#define CALIBRATED 		8
//#define NOT_CALIBRATED  9

/****
 * Description: Initialization of Different Application components
 * Args: None
 * Return: None
 * Ex: App_Init();
 */
void App_Init();	


/****
 * Description: Get mouse Direction from Gradient of head 
 * Args: None
 * Return: u8_t gradient_Direction -> (LEFT, RIGHT, UP, DOWN)
 * Ex: u8_t direction = App_GetImuGradient();
 */				
u8_t App_GetImuGradient(void);




/****
 * Description: Get the state of touch sensor -> pressed "device is dressed" or not
 * Args: None
 * Return: u8_t status (CONTACT, NOT_CONTACT)
 * Ex: u8_t state = App_GetTouchSensorState();
 */				
 
u8_t App_GetTouchSensorState(void);				


/****
 * Description: Get initial point that the others are measured relative to (calibration point)
 * Args: array of 3 elements[x,y,z] (float*)
 * Return: None
 * Ex: App_GetImuCalibPoint(reference_angles);
 */	
void App_GetImuCalibPoint(void);


/****
 * Description: check if sensors are calibrated successfully or not
 * Args: None
 * Return: calibration status [CALIBRATED, NOT_CALIBRATED] -> (u8_t)
 * Ex: u8_t calib_status = App_GetCalibStatus();
 */
u8_t App_GetCalibStatus(void);
// Logic					
/* get readings if reading > threshold in a certain direction take mouse action*/					
/* calibrate and set leds based on touch sensor readings*/					


/****
 * Description: order Mouse to do a certain action
 * Args: order (LEFT, RIGHT, UP, DOWN, LEFT_CLICK, RIGHT_CLICK) -> see App_config.h
 * Return: None
 * Ex: App_MoveMouse(LEFT_CLICK);
 */		
void App_OrderMouse(u8_t order);


u8_t App_SetReference(void);


#endif