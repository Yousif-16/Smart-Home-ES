/*
 * Keypad.c
 *
 * Created: 9/15/2022 4:36:45 PM
 *  Author: Dell
 */ 
#include "Keypad.h"

char arr[4][3] = {{'1','2','3'},
				   {'4','5','6'},
			       {'7','8','9'},
			       {'*','0','#'}}; 	   	   	

void Keypad_Init()
{
	DIO_SetPin_Dir(Keypad_Row_Port, Keypad_Row_PIN_0, PIN_IN);
	DIO_SetPin_Dir(Keypad_Row_Port, Keypad_Row_PIN_1, PIN_IN);
	DIO_SetPin_Dir(Keypad_Row_Port, Keypad_Row_PIN_2, PIN_IN);
	DIO_SetPin_Dir(Keypad_Row_Port, Keypad_Row_PIN_3, PIN_IN);
	
	DIO_SetPin_Pullup(Keypad_Row_Port, Keypad_Row_PIN_0);
	DIO_SetPin_Pullup(Keypad_Row_Port, Keypad_Row_PIN_1);
	DIO_SetPin_Pullup(Keypad_Row_Port, Keypad_Row_PIN_2);
	DIO_SetPin_Pullup(Keypad_Row_Port, Keypad_Row_PIN_3);
	
	DIO_SetPin_Dir(Keypad_Column_Port, Keypad_Column_PIN_0, PIN_OUT);
	DIO_SetPin_Dir(Keypad_Column_Port, Keypad_Column_PIN_1, PIN_OUT);
	DIO_SetPin_Dir(Keypad_Column_Port, Keypad_Column_PIN_2, PIN_OUT);
	//DIO_SetPin_Dir(Keypad_Column_Port, Keypad_Column_PIN_3, PIN_OUT);
	
	DIO_SetPin_Value(Keypad_Column_Port, Keypad_Column_PIN_0, PIN_ON);
	DIO_SetPin_Value(Keypad_Column_Port, Keypad_Column_PIN_1, PIN_ON);
	DIO_SetPin_Value(Keypad_Column_Port, Keypad_Column_PIN_2, PIN_ON);
	//DIO_SetPin_Value(Keypad_Column_Port, Keypad_Column_PIN_3, PIN_ON);
}

Uint8 Keypad_GetValue()
{
	Uint8 Value = 0;
	
	for(Uint8 i = Keypad_Column_PIN_0; i <= Keypad_Column_PIN_2; i++)
	{
		DIO_SetPin_Value(Keypad_Column_Port, i, PIN_OFF);
		for(Uint8 j = Keypad_Row_PIN_0; j <= Keypad_Row_PIN_3; j++)
		{
			if(!DIO_GetPin_Value(Keypad_Row_Port, j))
			{
				Value = arr[j-Keypad_Row_PIN_0][i-Keypad_Column_PIN_0];
				while(!DIO_GetPin_Value(Keypad_Row_Port, j));
			} 
		}
		DIO_SetPin_Value(Keypad_Column_Port, i, PIN_ON);
	}
	return Value;
}