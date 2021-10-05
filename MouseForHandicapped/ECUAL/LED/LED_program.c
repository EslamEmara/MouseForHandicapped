/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 21 2021                              */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "LED_interface.h"


void LED_Init(u8 copy_u8Port , u8 copy_u8Pin)
{
	GPIO_setPinDirection(copy_u8Port ,copy_u8Pin, OUTPUT );	
}


void LED_TurnOn(u8 copy_u8Port , u8 copy_u8Pin)
{
	MGPIO_voidSetPinValue( copy_u8Port , copy_u8Pin , HIGH );
}


void LED_TurnOff(u8 copy_u8Port , u8 copy_u8Pin)
{
     MGPIO_voidSetPinValue(copy_u8Port , copy_u8Pin , LOW );
}
