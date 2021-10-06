/*
 * Math.h
 *
 * Created: 9/2/2021 11:31:34 AM
 *  Author: Eslam Emara
 */ 


#ifndef MATH_H_
#define MATH_H_


#define SETBIT(reg,n)		( (reg) |= ( 1<< (n) ) )
#define CLRBIT(reg,n)		((reg)&= ~(1<<(n)))
#define GETBIT(reg,n)		(((reg)>>(n)) & 1)
#define TOGGLEBIT(reg,n)	((reg) ^= (1<<(n)))

#endif /* MATH_H_ */