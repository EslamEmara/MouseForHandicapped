/*
 * Mouse.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef MOUSE_H_
#define MOUSE_H_
#include "../../MCAL/USB/usbdrv.h"
#include "../../MCAL/USB/oddebug.h"        /* This is also an example for using debug macros */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */



typedef struct{
	unsigned char   buttonMask;
	char    dx;
	char    dy;
	char    dWheel;
}report_t;

void Mouse_init (void) ; 
void Mouse_MoveLeft(void) ; 
void Mouse_MoveRight(void) ;	
void Mouse_MoveUp(void) ;
void Mouse_MoveDown(void) ;			
void Mouse_RightClick(void) ;
void Mouse_LeftClick(void);	



#endif /* MOUSE_H_ */