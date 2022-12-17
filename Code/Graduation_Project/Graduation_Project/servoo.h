/*
 * servoo.h
 *
 * Created: 18/10/2022 04:27:23 م
 *  Author: User
 */ 


#ifndef SERVOO_H_
#define SERVOO_H_
#define F_CPU 16000000
#include "std.h"
#include <avr/io.h>

void Servoo_Motor(Uint32 duty_Cycle);
void Servo_INIT(void);
void Servo_Open(void);
void Servo_Close(void);




#endif /* SERVOO_H_ */