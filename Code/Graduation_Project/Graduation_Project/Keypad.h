/*
 * Keypad.h
 *
 * Created: 9/15/2022 4:35:49 PM
 *  Author: Dell
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "Keypad_Configuration.h"
#define NULL_KEYPAD '\0'

void Keypad_Init();
Uint8 Keypad_GetValue();




#endif /* KEYPAD_H_ */