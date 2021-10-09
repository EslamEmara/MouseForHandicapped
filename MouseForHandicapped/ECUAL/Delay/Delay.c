/*
 * Delay.c
 *
 * Created: 9/15/2021 1:22:25 PM
 *  Author: Farouk
 */ 

#include "../../MCAL/DIO/TypeDefs.h"

#include "Delay_interface.h"
#include "Delay_config.h"


#if KEY == TIMER //---------------------------------
#include "timer_interface.h"
#include "DIO_interface.h"



void Delay_Init(void)
{
	timer_init();
}



void Delay_ms(uint16_t ticks_num)
{
	timer_setInterval(ticks_num - OVERLOAD_TIME_MS);
	timer_setClk_start(TIMER0,CLK_DIV_1024);
	timer_waitFlag(OVERFLOW_FLAG);
}


void Delay_us(uint16_t ticks_num)
{
	timer_setInterval(ticks_num - OVERLOAD_TIME_US);
	timer_setClk_start(TIMER0,CLK_DIV_1);
	timer_waitFlag(OVERFLOW_FLAG);
}

#endif //-------------------------

void Delay_us_independent(u16_t time_us)
{
	time_us /= 3;
	while (time_us)
	{
		time_us--;
	}
}

void Delay_ms_independent(u16_t time_ms)
{
	u32_t num_of_ticks = time_ms;
	num_of_ticks = num_of_ticks*1000/3;
	while (num_of_ticks)
	{
		num_of_ticks--;
	}
}