/*
 * RegMap.h
 *
 * Created: 9/2/2021 10:31:05 AM
 *  Author: Eslam Emara
 */ 


#ifndef REGMAP_H_
#define REGMAP_H_

#define REG(n)				(*((volatile u8_t*)(n)))

#define PA_OUTDATA			(*((volatile u8_t*)(0x3B)))
#define PA_DIR				(*((volatile u8_t*)(0x3A)))
#define PA_INDATA			(*((volatile u8_t*)(0x39)))

#define PB_OUTDATA			(*((volatile u8_t*)(0x38)))
#define PB_DIR				(*((volatile u8_t*)(0x37)))
#define PB_INDATA			(*((volatile u8_t*)(0x36)))

#define PC_OUTDATA			(*((volatile u8_t*)(0x35)))
#define PC_DIR				(*((volatile u8_t*)(0x34)))
#define PC_INDATA			(*((volatile u8_t*)(0x33)))

#define PD_OUTDATA			(*((volatile u8_t*)(0x32)))
#define PD_DIR				(*((volatile u8_t*)(0x31)))
#define PD_INDATA			(*((volatile u8_t*)(0x30)))

#define PULL_UP_DISABLE		(*((volatile u8_t*)(0x50)))			//bit 2





#endif /* REGMAP_H_ */