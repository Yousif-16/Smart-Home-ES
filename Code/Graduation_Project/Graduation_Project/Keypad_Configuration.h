/*
 * Keypad_Configuration.h
 *
 * Created: 9/15/2022 4:36:23 PM
 *  Author: Dell
 */ 


#ifndef KEYPAD_CONFIGURATION_H_
#define KEYPAD_CONFIGURATION_H_
#include "DIO.h"

#define Keypad_Row_Port DIO_PORTA
#define Keypad_Column_Port DIO_PORTB

#define Keypad_Row_PIN_0 PIN_3
#define Keypad_Row_PIN_1 PIN_4
#define Keypad_Row_PIN_2 PIN_5
#define Keypad_Row_PIN_3 PIN_6

#define Keypad_Column_PIN_0 PIN_0
#define Keypad_Column_PIN_1 PIN_1
#define Keypad_Column_PIN_2 PIN_2
//#define Keypad_Column_PIN_3 PIN_6



#endif /* KEYPAD_CONFIGURATION_H_ */