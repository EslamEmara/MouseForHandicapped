


#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

/****
 * Description: Initialization of Different Application components
 * Args: None
 * Return: None
 * Ex: App_Init();
 */
void App_Init();	


/****
 * Description: Get Direction of Gradient of head 
 * Args: None
 * Return: uint8_t gradient_Direction -> (LEFT, RIGHT, UP, DOWN)
 * Ex: uint8_t direction = App_GetImuGradDirection();
 */				
uint8_t App_GetImuGradDirection(void);


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

// Logic					
/* get readings if reading > threshold in a certain direction take mouse action*/					
/* calibrate and set leds based on touch sensor readings*/					






#endif