/*
 * I2C_RegMaph.h
 *
 * Created: 9/25/2021 8:39:03 PM
 *  Author: 20109
 */ 


#ifndef I2C_REGMAPH_H_
#define I2C_REGMAPH_H_
#include "TypeDefs.h"

#define TWSR_REG				(*(volatile uint8_t*)(0x21))
#define TWBR_REG				(*(volatile uint8_t*)(0x20))
#define I2C_CONTROL_REG			(*(volatile uint8_t*)(0x56))
#define TWDR_REG				(*(volatile uint8_t*)(0x23))
#define TWAR_REG				(*(volatile uint8_t*)(0x22))

#define TWISTA				5
#define I2C_ENABLE_BIT		2
#define I2C_IF				7
#define TWSTO				4
#define TWEA				6

#define GENERATE_START			SETBIT(I2C_CONTROL_REG,TWISTA)
#define ENABLE_I2C				SETBIT(I2C_CONTROL_REG,I2C_ENABLE_BIT)
#define CLEAR_IF				SETBIT(I2C_CONTROL_REG,I2C_IF)
#define GENERATE_ACK			SETBIT(I2C_CONTROL_REG,TWEA)



#endif /* I2C_REGMAPH_H_ */