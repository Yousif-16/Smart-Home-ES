/*
 * DIO.h
 *
 * Created: 9/6/2022 2:15:36 PM
 *  Author: Dell
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "std.h"
#include "MCU_ATMEGA32.h"
#include "Bit_Math.h"

#define	DIO_PORTA 0
#define	DIO_PORTB 1
#define	DIO_PORTC 2
#define	DIO_PORTD 3

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

#define PIN_IN 0
#define PIN_OUT 1

#define PIN_ON 0
#define PIN_OFF 1

#define PIN_INTERNAL_PULLUP 0
#define PIN_INTERNAL_PULLDOWN 1
#define PIN_FLOATED 2

void DIO_SetPin_Dir(Uint8, Uint8, Uint8);

void DIO_SetPin_Value(Uint8, Uint8, Uint8);

Uint8 DIO_GetPin_Value(Uint8, Uint8);

void DIO_TogglePin_Value(Uint8, Uint8);

void DIO_SetPin_Pullup(Uint8, Uint8);


#endif /* DIO_H_ */