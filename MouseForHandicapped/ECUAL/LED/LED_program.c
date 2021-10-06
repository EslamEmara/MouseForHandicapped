/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 21 2021                              */
/*********************************************************/
#include "../../MCAL/DIO/TypeDefs.h"
#include "../../MCAL/DIO/DIO.h"
#include "LED_interface.h"


void LED_Init(uint8_t copy_u8Port , uint8_t copy_u8Pin)
{
	DIO_setPinDir(copy_u8Port ,copy_u8Pin, OUT );	
}


void LED_TurnOn(uint8_t copy_u8Port , uint8_t copy_u8Pin)
{
	DIO_setPin( copy_u8Port , copy_u8Pin);
}


void LED_TurnOff(uint8_t copy_u8Port , uint8_t copy_u8Pin)
{
     DIO_clearPin(copy_u8Port , copy_u8Pin);
}
