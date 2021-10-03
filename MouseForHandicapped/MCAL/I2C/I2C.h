/*
 * I2C.h
 *
 * Created: 9/25/2021 8:38:50 PM
 *  Author: 20109
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "BIT_MATH.h"
#include "I2C_RegMaph.h"

#define INIT_ERROR		0
#define SUCCESS			1
#define ACK_RECEIVED	2
#define NACK_RECEIVED	3
#define START_ERROR		4
#define HIGH_FIVE_BITS	(0xF8)

#define START_SUCCESS_STATUS	(0x08)
#define ACK_RECIEVED_STATUS		(0x18)
#define NACK_RECEIVED_STATUS	(0x28)



typedef enum{
	FREQ_1MHz,
	FREQ_2MHz,
	FREQ_4MHz,
	FREQ_8MHz,
	FREQ_16Mhz,
	
	}EN_ClockFreq_t;
	
	

uint8_t I2C_Init(EN_ClockFreq_t FCPU,uint32_t SCL_Freq);
uint8_t I2C_Master_Start(char write_address);						/* I2C start function */
void I2C_Start_Wait(char write_address);					/* I2C start wait function */
uint8_t I2C_Master_Write(char data);							/* I2C write function */
void I2C_Stop();												/* I2C stop function */
char I2C_Read_Ack();										/* I2C read ack function */
char I2C_Read_Nack();									/* I2C read nack function */

void I2C_Slave_Init(uint8_t slave_address);
sint8_t I2C_Slave_Listen();
char I2C_Slave_Receive();

#endif /* I2C_H_ */