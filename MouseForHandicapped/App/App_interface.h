


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

//------ Global Variables --------
 // X,Y,Z -> Roll,pitch,yaw
uint16_t angles[3];
uint16_t current_reading[3];


/* Movements of Mouse */
#define UP   	 		0
#define DOWN 	 		1
#define LEFT 	 		2
#define RIGHT    		3
#define LEFT_CLICK		4
#define RIGHT_CLICK		5
#define NOTHING			255

/* Touch Sensor Status */
#define CONTACT			6
#define NOT_CONTACT		7

/* Calibration Status */
#define CALIBRATED 		8
#define NOT_CALIBRATED  9

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
 * Return: uint8_t gradient_Direction -> (LEFT, RIGHT, UP, DOWN)
 * Ex: uint8_t direction = App_GetImuGradient();
 */				
uint8_t App_GetImuGradient(void);


/****
 * Description: Move Mouse in certain direction
 * Args: movement (LEFT, RIGHT, UP, DOWN) -> see App_config.h
 * Return: None
 * Ex: App_MoveMouse(LEFT);
 */				
void App_MoveMouse(uint8_t movement);


/****
 * Description: Get the state of touch sensor -> pressed "device is dressed" or not
 * Args: None
 * Return: uint8_t status (CONTACT, NOT_CONTACT)
 * Ex: uint8_t state = App_GetTouchSensorState();
 */				
 
uint8_t App_GetTouchSensorState(void);				


/****
 * Description: Get initial point that the others are measured relative to (calibration point)
 * Args: array of 3 elements[x,y,z] (float*)
 * Return: None
 * Ex: App_GetImuCalibPoint(angles);
 */	
void App_GetImuCalibPoint(float angles[]);


/****
 * Description: check if sensors are calibrated successfully or not
 * Args: None
 * Return: calibration status [CALIBRATED, NOT_CALIBRATED] -> (uint8_t)
 * Ex: uint8_t calib_status = App_GetCalibStatus();
 */
uint8_t App_GetCalibStatus(void);
// Logic					
/* get readings if reading > threshold in a certain direction take mouse action*/					
/* calibrate and set leds based on touch sensor readings*/					






#endif