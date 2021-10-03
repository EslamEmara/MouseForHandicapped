/*
 * BIT_MATH.h
 *
 * Created: 9/4/2021 6:13:46 AM
 *  Author: Eslam Emara
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_




#define SETBIT(reg,n)		( (reg) |= ( 1<< (n) ) )
#define CLRBIT(reg,n)		((reg)&= ~(1<<(n)))
#define GETBIT(reg,n)		(((reg)>>(n)) & 1)
#define TOGGLEBIT(reg,n)	((reg) ^= (1<<(n)))


#endif /* BIT_MATH_H_ */