/*
 * Relay.c
 *
 * Created: 9/8/2022 3:13:04 PM
 *  Author: Dell
 */
#include "Relay.h" 

/*---------------Relay--------------*/
void Relay_Init(void)
{
	DIO_SetPin_Dir(Relay_Port, Relay_Pin, PIN_OUT);
	DIO_SetPin_Value(Relay_Port, Relay_Pin, PIN_OFF);
}

void Relay_ON(void)
{
	DIO_SetPin_Value(Relay_Port, Relay_Pin, PIN_ON);
}
void Relay_OFF(void)
{
	DIO_SetPin_Value(Relay_Port, Relay_Pin, PIN_OFF);
}

void Relay_Toggle(void)
{
	DIO_TogglePin_Value(Relay_Port, Relay_Pin);
}
