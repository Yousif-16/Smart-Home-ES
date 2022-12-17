/*
 * EXT_Interrupt.h
 *
 * Created: 9/21/2022 12:27:18 PM
 *  Author: Dell
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_
#include "EXT_Interrupt_Configuration.h"

#include "LCD.h"
#include "Keypad.h"
#include "std.h"
#include "LED.h"
#include "EEPROM.h"
#include "ALARM.h"
#include "servoo.h"
#include "UART.h"
#include "Timer.h"
#include "servoo.h"

/*INT0 Triggers*/
#define EXt0_Low_Level 0
#define EXt0_Level_Change 1
#define EXt0_Falling_Edge 2
#define EXt0_Rising_Edge 3

/*INT1 Triggers*/
#define EXt1_Low_Level 0
#define EXt1_Level_Change 1
#define EXt1_Falling_Edge 2
#define EXt1_Rising_Edge 3

/*INT2 Triggers*/
#define EXt2_Falling_Edge 0
#define EXt2_Rising_Edge 1

void INT0_Init(void);
void INT1_Init(void);
void INT2_Init(void);
void LCD_LogIN_system(void);
void Door(void);



#endif /* EXT_INTERRUPT_H_ */