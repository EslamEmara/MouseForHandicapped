/*
 * DIO.h
 *
 * Created: 9/2/2021 10:30:39 AM
 *  Author: Eslam Emara
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "TypeDefs.h"
#include "RegMap.h"
#include "Math.h"

	typedef enum dir{
		IN,
		OUT,
		PULLUP,
	}EN_DIR_t;
	typedef enum Ports {
		PORTA = 0x3B,
		PORTB = 0x38,
		PORTC = 0x35,
		PORTD = 0x32,
		}EN_PORTS_t;
	
	typedef enum PINS {
		PIN0 = 0,
		PIN1,
		PIN2,
		PIN3,
		PIN4,
		PIN5,
		PIN6,
		PIN7,
	}EN_PINS_t;
	
	typedef enum data {
		LOW,
		HIGH,
	}EN_DATA_t;

	typedef struct DIOconfig
	{
		EN_PORTS_t PORT;
		EN_DIR_t DIR[8]; 
		
	}ST_DIO_config_t;
	
	void DIO_init(ST_DIO_config_t configs);		
	
	void DIO_setPinDir(EN_PORTS_t port , EN_PINS_t pin ,EN_DIR_t DIR);
	void DIO_setPortDir(EN_PORTS_t port , EN_DIR_t dir);
	EN_DIR_t DIO_getPinDir(EN_PORTS_t port,EN_PINS_t pin);

	
	void DIO_write(EN_PORTS_t port,EN_PINS_t pin,EN_DATA_t data );
	void DIO_writePort(EN_PORTS_t port,uint8_t bin_pins);
	void DIO_setPin(EN_PORTS_t port,EN_PINS_t pin);
	void DIO_clearPin(EN_PORTS_t port,EN_PINS_t pin);

	uint8_t DIO_getPin(EN_PORTS_t port,EN_PINS_t pin);
	void DIO_toggle(EN_PORTS_t port,EN_PINS_t pin);
	
#endif