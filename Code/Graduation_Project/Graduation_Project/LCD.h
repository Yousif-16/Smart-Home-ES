/*
 * LCD.h
 *
 * Created: 9/12/2022 4:32:00 PM
 *  Author: Dell
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "LCD_Configuration.h"

#define Clear_Display_Screen 0x01

#define Return_Home 0x02

#define Shift_Cursor_Left_Per_Read_Write 0x04
#define Shift_Cursor_Right_Per_Read_Write 0x06
#define Shift_Display_Right_Per_Read_Write 0x05
#define Shift_Display_Left_Per_Read_Write 0x07

#define Display_Cursor_Blink_All_OFF 0x08
#define Display_Cursor_OFF_Blink_ON 0x09
#define Display_Blink_OFF_Cursor_ON 0x0A
#define Display_OFF_Cursor_Blink_ON 0x0B
#define Display_ON_Cursor_Blink_OFF 0x0C
#define Display_Blink_ON_Cursor_OFF 0x0D
#define Display_Cursor_ON_Blink_OFF 0x0E
#define Display_Cursor_Blink_All_ON 0x0F

#define Shift_Cursor_Position_Left 0x10
#define Shift_Cursor_Position_Right 0x14
#define Shift_Entire_Display_Left 0x18
#define Shift_Entire_Display_Right 0x1C

#define LCD_4_Bit_Mode_1_Line_5_8_Dots 0x20
#define LCD_4_Bit_Mode_2_Line_5_8_Dots 0x28
#define LCD_8_Bit_Mode_1_Line_5_8_Dots 0x30
#define LCD_8_Bit_Mode_2_Line_5_8_Dots 0x38

#define DDRAM_Cursor_Begin_1st_Line 0x80
#define DDRAM_Cursor_Begin_2st_Line	0xC0

#define CGRAM_First_Address_First_Character 0X40

#define _4_Bit_Mode 0
#define _8_Bit_Mode 1

void LCD_Init(void);
void LCD_Write_CMD(Uint8 cmd);
void LCD_Write_Char(Uint8 data);
void LCD_Write_String(Uint8* str);
void LCD_Write_Integer(Uint32 data);
void LCD_Write_Decimal(f32 data);
void LCD_Goto(Uint8 row, Uint8 column);
void LCD_Write_Custom_Char(char *arr, char Position);
void LCD_Clear(void);

#endif /* LCD_H_ */