/*
 * Mouse.c
 *
 *  Author: Mahmoud Ayoub
 */ 

#include "Mouse.h"

static report_t reportBuffer;

void Mouse_init (void) {
	/*  initialize INT0   */ 
}
void Mouse_MoveLeft(void) {
	reportBuffer.dx = -1 ;
}
void Mouse_MoveRight(void) {
	reportBuffer.dx = 1 ; 
}
void Mouse_MoveUp(void) {
	reportBuffer.dy = -1 ; 
}
void Mouse_MoveDown(void) {
	reportBuffer.dy = 1 ;
}
void Mouse_RightClick(void) {
	reportBuffer.buttonMask = 1 ; 
}
void Mouse_LeftClick(void) {
	reportBuffer.buttonMask = 2 ;
}