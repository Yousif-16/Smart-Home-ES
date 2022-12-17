#include "Buzzer.h"

/*---------------Buzzer--------------*/
void Buzzer_Init(void)
{
	DIO_SetPin_Dir(Buzzer_Port, Buzzer_Pin, PIN_OUT);
	DIO_SetPin_Value(Buzzer_Port, Buzzer_Pin, PIN_OFF);
}

void Buzzer_ON(void)
{
	DIO_SetPin_Value(Buzzer_Port, Buzzer_Pin, PIN_ON);
}
void Buzzer_OFF(void)
{
	DIO_SetPin_Value(Buzzer_Port, Buzzer_Pin, PIN_OFF);
}

void Buzzer_Toggle(void)
{
	DIO_TogglePin_Value(Buzzer_Port, Buzzer_Pin);
}
/*
 * Buzzer.c
 *
 * Created: 9/8/2022 3:19:09 PM
 *  Author: Dell
 */ 
