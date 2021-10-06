/*
* DIO.c
*
* Created: 9/2/2021 10:30:19 AM
*  Author: Eslam Emara
*/ 
#include "DIO.h"

/*
* DIO initialization function that sets the directions of port pins
* INPUTS : ST_DIO_config_t of	EN_PORTS_t PORT; EN_DIR_t DIR[8] (see definition of enums and struct in DIO.h file)
* void return.
*EX: ST_DIO_config_t config; config.port = PORTA ; config.DIR[0] = OUT;
*    DIO_init(config)
* this example initializes pin 0 of portA as output
*/
void DIO_init(ST_DIO_config_t configs)
{	
	uint8_t i =0;
	for(i=0; i<8;i++)
	{
		if(configs.DIR[i] == OUT){
			SETBIT(REG(configs.PORT-0x01) ,i);				// direction register always = port reg - 0x01
		}
		else if(configs.DIR[i] == IN){
			CLRBIT(REG(configs.PORT - 0x01) ,i);			//clear direction register
			SETBIT(PULL_UP_DISABLE,2);						//disable pull up in reg
			SETBIT(REG(configs.PORT) ,i);					//set port pin	(according to data sheet)
		}
			
		else if (configs.DIR[i] == PULLUP){					//PULLUP MODE
			CLRBIT(REG(configs.PORT - 0x01) ,i);			//clear direction register
			CLRBIT(PULL_UP_DISABLE,2);						//enable pull up reg
			SETBIT(REG(configs.PORT) ,i);					//set port pin (according to data sheet)
		}
	}

}
/*
* Function to set pin direction directly 
* Inputs: EN_PORTS_t holds the port name
EN_PINS_t holds the pin number
EN_DIR_t holds the desired direction
(see DIO.h to see the enums definitions)
* void return.
*/
void DIO_setPinDir(EN_PORTS_t port , EN_PINS_t pin ,EN_DIR_t DIR)
{
	if (DIR == OUT){
		SETBIT(REG(port - 0x01) ,pin);					// direction register always = port reg - 0x01
	}
			
	else if(DIR == IN){
		CLRBIT(REG(port - 0x01) ,pin);					//clear direction register
		SETBIT(PULL_UP_DISABLE,2);						//disable pull up
		SETBIT(REG(port) ,pin);							//set port pin	(according to datasheet)
	}
		
	else if (DIR == PULLUP){					//PULLUP MODE
		CLRBIT(REG(port - 0x01) ,pin);			//clear direction register
		CLRBIT(PULL_UP_DISABLE,2);				//enable pull up
		SETBIT(REG(port) ,pin);					//set port pin (according to datasheet)
	}
}
/*function the set the whole port direction to a desired direction
*inputs: EN_PORTS_t port ,  EN_DIR_t desired direction
*void return.
*/
void DIO_setPortDir(EN_PORTS_t port , EN_DIR_t dir)
{
	if (dir == OUT){
		REG(port - 0x01) = 0xFF;					// direction register always = port reg - 0x01
	}
		
	else if(dir == IN){
		REG(port - 0x01) = 0x00;					//clear direction register
		SETBIT(PULL_UP_DISABLE,2);					//disable pull up
		REG(port) =0xFF;							//set port 	(according to datasheet)
	}
		
	else if (dir == PULLUP){					//PULLUP MODE
		REG(port - 0x01) = 0x00;				//clear direction register
		CLRBIT(PULL_UP_DISABLE,2);				//enable pull up
		REG(port) = 0xFF;						//set port pin (according to datasheet)
	}
}
/*function to write data to a certain pin (high or low)
*Inputs : EN_PORTS_t port ,EN_PINS_t pin no,EN_DATA_t HIGH or LOW
* void return.
*/
void DIO_write(EN_PORTS_t port,EN_PINS_t pin,EN_DATA_t data )
{
	if (data == HIGH){
		SETBIT(REG(port),pin);
	}
	else{
		CLRBIT(REG(port),pin);
	}
}
/*
*Function to set Pin to High 
*Inputs : EN_PORTS_t port ,EN_PINS_t pin no
*/
void DIO_setPin(EN_PORTS_t port,EN_PINS_t pin)
{
	SETBIT(REG(port),pin);
}
/*
*Function to write data to the whole port 
*Inputs : EN_PORTS_t port ,uint8_t data
* EX: DIO_writePort(PORTA,0x0F);
* this example set the first 4 bits to 0xF HIGH and the last 4 bits to 0x0 LOW
* void return.
*/
void DIO_writePort(EN_PORTS_t port,uint8_t bin_pins)
{
	REG(port)=bin_pins;
}
	
/*
*Function to clear Pin to LOW 
*Inputs : EN_PORTS_t port ,EN_PINS_t pin no
*/	
void DIO_clearPin(EN_PORTS_t port,EN_PINS_t pin)
{
	CLRBIT(REG(port),pin);
}

/*
*Function to return Pin data 
*Inputs : EN_PORTS_t port ,EN_PINS_t pin no
* return uint8_t that holds the input value
*/	
uint8_t DIO_getPin(EN_PORTS_t port,EN_PINS_t pin)
{
	return GETBIT(REG(port-0x02),(uint8_t)pin);
}
	
/*
*Function to toggle Pin data 
*Inputs : EN_PORTS_t port ,EN_PINS_t pin no
* return void
*/		
void DIO_toggle(EN_PORTS_t port,EN_PINS_t pin)
{
	TOGGLEBIT(REG(port),pin);
}
	
/*
*Function to return Pin direction 
*Inputs : EN_PORTS_t port ,EN_PINS_t pin no
* return EN_DIR_t that holds the pin direction
*/
EN_DIR_t DIO_getPinDir(EN_PORTS_t port,EN_PINS_t pin)
{
	if (GETBIT(REG(port - 0x01),pin) == 1)
		return OUT;
	else 
	{
		if (GETBIT(PULL_UP_DISABLE,2) == 1)
			return IN;
		else 
			return PULLUP;
	}
}