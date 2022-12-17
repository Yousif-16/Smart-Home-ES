/*
 * LCD.c
 *
 * Created: 9/12/2022 4:32:49 PM
 *  Author: Dell
 */ 
#define  F_CPU 16000000
#include <util/delay.h>
#include "LCD.h"

void LCD_Init(void)
{
	#if LCD_Interface_Mode == _4_Bit_Mode
	DIO_SetPin_Dir(LCD_4_Bit_Control_Port ,LCD_RS_PIN ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Control_Port ,LCD_RW_PIN ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OUT);
	
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D4 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D5 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D6 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D7 ,PIN_OUT);
	
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RS_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RW_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D4 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D5 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D6 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D7 ,PIN_OFF);
		
	_delay_ms(100);
	
	LCD_Write_CMD(0X33);
	LCD_Write_CMD(0X32);
	LCD_Write_CMD(LCD_4_Bit_Mode_2_Line_5_8_Dots);
	LCD_Write_CMD(Clear_Display_Screen);
	LCD_Write_CMD(Return_Home);
	LCD_Write_CMD(Shift_Cursor_Right_Per_Read_Write);
	LCD_Write_CMD(Display_Cursor_ON_Blink_OFF);
	
	#elif LCD_Interface_Mode == _8_Bit_Mode
	DIO_SetPin_Dir(LCD_4_Bit_Control_Port ,LCD_RS_PIN ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Control_Port ,LCD_RW_PIN ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OUT);
	
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D0 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D1 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D2 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D3 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D4 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D5 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D6 ,PIN_OUT);
	DIO_SetPin_Dir(LCD_4_Bit_Data_Port ,LCD_D7 ,PIN_OUT);
	
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RS_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RW_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D0 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D1 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D2 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D3 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D4 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D5 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D6 ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Data_Port ,LCD_D7 ,PIN_OFF);
	
	#endif
}

void LCD_Write_CMD(Uint8 cmd)
{
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RS_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RW_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
	LCD_4_Bit_Data_Bus = (cmd & 0XF0) | (LCD_4_Bit_Data_Bus & 0X0F);
	
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_ON);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
	LCD_4_Bit_Data_Bus = (cmd << 4) | (LCD_4_Bit_Data_Bus & 0X0F);
     
	 DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_ON);
	 _delay_ms(1);
	 DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	 
	 _delay_ms(5);
}

void LCD_Write_Char(Uint8 data)
{
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RS_PIN ,PIN_ON);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_RW_PIN ,PIN_OFF);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
	LCD_4_Bit_Data_Bus = (data & 0XF0) | (LCD_4_Bit_Data_Bus & 0X0F);
	
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_ON);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
	LCD_4_Bit_Data_Bus = (data << 4) | (LCD_4_Bit_Data_Bus & 0X0F);
	
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_ON);
	_delay_ms(1);
	DIO_SetPin_Value(LCD_4_Bit_Control_Port ,LCD_E_PIN ,PIN_OFF);
	
}
void LCD_Write_String(Uint8* str)
{
	Uint8 i = 0;
	while(str[i] != '\0')
	{
		LCD_Write_Char(str[i]);
		i++;
	}
}

void LCD_Write_Integer(Uint32 data)
{
	int num = 0, multiplier = 1, i = 0;
	if(!data)
	{
		LCD_Write_Char('0');
	}
	else if(data < 0)
	{
		LCD_Write_Char('-');
		data *= -1;
	}
	while(data)
	{
		num = (num*10) + (data%10);
		
		if(!num)
			multiplier *= 10;
		
		data /= 10;
	}
	while(num != i)
	{
		LCD_Write_Char(num%10 + 48);
		num /= 10;
		
		if(!num && multiplier >= 10)
		{
			i = 1;
			num = multiplier;
		}
	}
}

void LCD_Write_Decimal(f32 data)
{
	Uint32 num = 0;
	num = data;
	LCD_Write_Integer(num);
	LCD_Write_Char('.');
	data -= num;
	for(Uint8 i = 0; i < 3; i++)
	{
		data *= 10;
		num = data;
		LCD_Write_Char(num + 48);
		data -= num;
	}
}

void LCD_Clear(void)
{
	LCD_Write_CMD(Clear_Display_Screen);
}

void LCD_Goto(Uint8 row, Uint8 column)
{
	Uint8 arr[2] = {DDRAM_Cursor_Begin_1st_Line, DDRAM_Cursor_Begin_2st_Line};
		
	row = (row >= 0) && (row <= 1)? row : 0;
	column = (column >= 0) && (column <= 39)? column : 0; 
	
	LCD_Write_CMD(arr[row] + column);	
}

void LCD_Write_Custom_Char(char *arr, char Position)
{
	LCD_Write_CMD(CGRAM_First_Address_First_Character + (Position * 8));
	for(Uint8 i = 0; i < 8; i++)
	{
		LCD_Write_Char(arr[i]);
	}
}