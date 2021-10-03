/*
 * I2C.c
 *
 * Created: 9/25/2021 8:38:41 PM
 *  Author: 20109
 */ 
#include <math.h>

#include "I2C.h"


uint8_t I2C_Init(EN_ClockFreq_t FCPU,uint32_t SCL_Freq){
	
	uint8_t TWSR_value = 0;
	uint8_t found = 0;
	float test_equation = log(4)*(((FCPU / SCL_Freq) -16)/510);
	if (test_equation < 0){
		return INIT_ERROR;
	}
	for (TWSR_value = 0 ; TWSR_value <= 4 ; TWSR_value ++){
		if (test_equation <= (float)TWSR_value){
			TWSR_REG =TWSR_value;
			found = 1;
			break;
		}
	}
	if (found == 1){
		TWBR_REG =(uint8_t) (((FCPU / SCL_Freq) -16) / (2 * pow(4,TWSR_value)));
		return SUCCESS;
	}
	else {
		return INIT_ERROR;
	}
}
void I2C_Start_Wait(char write_address)						/* I2C start wait function */
{
	uint8_t status;											
	
	while (1)
	{
		GENERATE_START;
		ENABLE_I2C;
		CLEAR_IF;		
		while (!GETBIT(I2C_CONTROL_REG,I2C_IF));								
		status=TWSR_REG&HIGH_FIVE_BITS;		
		if (status != 0x08)									
			continue;											
		TWDR_REG = write_address;
		ENABLE_I2C;
		CLEAR_IF;

		while (GETBIT(I2C_CONTROL_REG,I2C_IF) == 0);
		status=TWSR_REG&HIGH_FIVE_BITS;
		if (status != 0x18 )
		{
			I2C_Stop();
			continue;
		}
		break;						
	}
}

uint8_t I2C_Master_Start(char write_address)						
{
	uint8_t status;		
	GENERATE_START;
	ENABLE_I2C;
	CLEAR_IF;
	
	while (!GETBIT(I2C_CONTROL_REG,I2C_IF));								
	
	status=TWSR_REG&HIGH_FIVE_BITS;		
	if(status!=0x08)		
		return 0;
															
	/*----------------------------------------*/
	TWDR_REG = write_address;													
	ENABLE_I2C;
	CLEAR_IF;

	while (GETBIT(I2C_CONTROL_REG,I2C_IF) == 0);								
	status=TWSR_REG&HIGH_FIVE_BITS;		
	if(status==0x18)		
		return 1;			
	if(status==0x20)		
		return 2;			
	else
		return 3;

}
uint8_t I2C_Master_Write(char data)							
{
	uint8_t status;		

	TWDR_REG = data;											
	ENABLE_I2C;
	CLEAR_IF;
	
	while (!GETBIT(I2C_CONTROL_REG,I2C_IF));							
	status=TWSR_REG&HIGH_FIVE_BITS;		
	if(status==0x28)		
		return 0;			
	if(status==0x30)		
		return 1;			
	else
		return 2;
}
uint8_t I2C_Repeated_Start(char read_address) 
{
	uint8_t status;		
	ENABLE_I2C;
	CLEAR_IF;
	GENERATE_START;
	while (!GETBIT(I2C_CONTROL_REG,I2C_IF));							
	status=TWSR_REG&HIGH_FIVE_BITS;
	if(status!=0x10)		
		return 0;			
		
	TWDR_REG=read_address;		
	ENABLE_I2C;
	CLEAR_IF;
	while (!GETBIT(I2C_CONTROL_REG,I2C_IF));							
	status=TWSR_REG&HIGH_FIVE_BITS;
	if(status==0x40)		
		return 1;		
	if(status==0x48)	
		return 2;			
	else
		return 3;			
}

void I2C_Stop()												
{
	ENABLE_I2C;
	CLEAR_IF;
	SETBIT(I2C_CONTROL_REG,TWSTO);
	while(GETBIT(I2C_CONTROL_REG,TWSTO));								
}
char I2C_Read_Ack()											
{
	ENABLE_I2C;
	CLEAR_IF;
	GENERATE_ACK;
		
	while (!GETBIT(I2C_CONTROL_REG,I2C_IF));							
	return TWDR_REG;											
}

char I2C_Read_Nack()										
{
	ENABLE_I2C;
	CLEAR_IF;
	
	while (!GETBIT(I2C_CONTROL_REG,I2C_IF));							
	return TWDR_REG;											
}

void I2C_Slave_Init(uint8_t slave_address)
{
	TWAR_REG=slave_address;		
	ENABLE_I2C;
	GENERATE_ACK;
	CLEAR_IF;
}

sint8_t I2C_Slave_Listen()
{
	uint8_t status;			
	while(1)
	{
		while(!GETBIT(I2C_CONTROL_REG,I2C_IF));
		status=TWSR_REG & HIGH_FIVE_BITS;		
		if(status==0x60||status==0x68)	
			return 0;			
		if(status==0xA8||status==0xB0)	
			return 1;			
		if(status==0x70||status==0x78)	
			return 2;			
		else
			continue;			
	}
}
sint8_t I2C_Slave_Receive()
{
	uint8_t status;		
	ENABLE_I2C;
	GENERATE_ACK;
	CLEAR_IF;
	while(!GETBIT(I2C_CONTROL_REG,I2C_IF));
	status=TWSR_REG & HIGH_FIVE_BITS;		
	
	if(status==0x80||status==0x90)
		return TWDR_REG;		
	if(status==0x88||status==0x98)
		return TWDR_REG;		
	if(status==0xA0){
		CLEAR_IF;
		return -1;
	}
	else
		return -2;			
}
sint8_t I2C_Slave_Transmit(char data)
{
	uint8_t status;
	TWDR=data;			/* Write data to TWDR to be transmitted */
	ENABLE_I2C;
	GENERATE_ACK;
	CLEAR_IF;
	while(!GETBIT(I2C_CONTROL_REG,I2C_IF));
	status=TWSR_REG & HIGH_FIVE_BITS;
	if(status==0xA0)		/* Check for STOP/REPEATED START received */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}
	if(status==0xB8)		/* Check for data transmitted &ack received */
	return 0;				/* If yes then return 0 */
	if(status==0xC0)		/* Check for data transmitted &nack received */
	{
		CLEAR_IF;
		return -2;
	}
	if(status==0xC8)		/* Last byte transmitted with ack received */
	return -3;				/* If yes then return -3 */
	else					/* else return -4 */
	return -4;
}