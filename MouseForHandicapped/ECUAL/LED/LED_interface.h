/*******************************************************/
/* author  : Farouk                                    */
/* Version : v01                                       */
/* Date    : Sept 21 2021                              */
/********************** ********************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


#define LED_RED		GPIOA, PIN0
#define LED_GREEN		GPIOA, PIN1


void LED_Init(u8 copy_u8Port , u8 copy_u8Pin);
void LED_TurnOn(u8 copy_u8Port , u8 copy_u8Pin);
void LED_TurnOff(u8 copy_u8Port , u8 copy_u8Pin);
#endif
