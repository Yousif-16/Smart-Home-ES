/*
 * LCD_Configuration.h
 *
 * Created: 9/12/2022 4:32:26 PM
 *  Author: Dell
 */ 


#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_
#include "DIO.h"

#define LCD_4_Bit_Data_Port DIO_PORTB
#define LCD_4_Bit_Data_Bus PORTB  
#define LCD_8_Bit_Data_Port DIO_PORTB

#define LCD_4_Bit_Control_Port DIO_PORTA
#define LCD_8_Bit_Control_Port DIO_PORTA

#define LCD_Interface_Mode _4_Bit_Mode

#define LCD_RS_PIN PIN_0
#define LCD_RW_PIN PIN_1
#define LCD_E_PIN PIN_2

#define LCD_D0 PIN_0
#define LCD_D1 PIN_1
#define LCD_D2 PIN_2
#define LCD_D3 PIN_3
#define LCD_D4 PIN_4
#define LCD_D5 PIN_5
#define LCD_D6 PIN_6
#define LCD_D7 PIN_7

#endif /* LCD_CONFIGURATION_H_ */