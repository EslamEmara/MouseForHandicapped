/*******************************************************/
/* author  : Farouk                                    */
/* Version : v01                                       */
/* Date    : Sept 21 2021                              */
/********************** ********************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


#define LED_RED			PORTA, PIN0
#define LED_GREEN		PORTA, PIN1


void LED_Init(u8_t copy_u8Port , u8_t copy_u8Pin);
void LED_TurnOn(u8_t copy_u8Port , u8_t copy_u8Pin);
void LED_TurnOff(u8_t copy_u8Port , u8_t copy_u8Pin);
#endif
