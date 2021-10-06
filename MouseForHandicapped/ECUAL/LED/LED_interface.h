/*******************************************************/
/* author  : Farouk                                    */
/* Version : v01                                       */
/* Date    : Sept 21 2021                              */
/********************** ********************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H


#define LED_RED			PORTA, PIN0
#define LED_GREEN		PORTA, PIN1


void LED_Init(uint8_t copy_u8Port , uint8_t copy_u8Pin);
void LED_TurnOn(uint8_t copy_u8Port , uint8_t copy_u8Pin);
void LED_TurnOff(uint8_t copy_u8Port , uint8_t copy_u8Pin);
#endif
