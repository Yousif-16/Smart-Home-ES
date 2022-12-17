/*
 * DIO.c
 *
 * Created: 9/6/2022 2:15:55 PM
 *  Author: Dell
 */ 
#include "DIO.h"

void DIO_SetPin_Dir(Uint8 port_name, Uint8 pin_name, Uint8 pin_dir)
{
	switch(pin_dir)
	{
		case PIN_IN:
		switch(port_name)
		{
			case DIO_PORTA:
			Clear_Bit(DDRA,pin_name);
			break;
			case DIO_PORTB:
			Clear_Bit(DDRB,pin_name);
			break;
			case DIO_PORTC:
			Clear_Bit(DDRC,pin_name);
			break;
			case DIO_PORTD:
			Clear_Bit(DDRD,pin_name);
			break;
			default:
			break;
		}
		break;
		case PIN_OUT:
		switch(port_name)
		{
			case DIO_PORTA:
			Set_Bit(DDRA,pin_name);
			break;
			case DIO_PORTB:
			Set_Bit(DDRB,pin_name);
			break;
			case DIO_PORTC:
			Set_Bit(DDRC,pin_name);
			break;
			case DIO_PORTD:
			Set_Bit(DDRD,pin_name);
			break;
			default:
			break;
		}
		break;
		default:
		break;
	}
}

void DIO_SetPin_Value(Uint8 port_name, Uint8 pin_name, Uint8 pin_value)
{
	switch(pin_value)
	{
		case PIN_OFF:
		switch(port_name)
		{
			case DIO_PORTA:
			Clear_Bit(PORTA,pin_name);
			break;
			case DIO_PORTB:
			Clear_Bit(PORTB,pin_name);
			break;
			case DIO_PORTC:
			Clear_Bit(PORTC,pin_name);
			break;
			case DIO_PORTD:
			Clear_Bit(PORTD,pin_name);
			break;
			default:
			break;
		}
		break;
		case PIN_ON:
		switch(port_name)
		{
			case DIO_PORTA:
			Set_Bit(PORTA,pin_name);
			break;
			case DIO_PORTB:
			Set_Bit(PORTB,pin_name);
			break;
			case DIO_PORTC:
			Set_Bit(PORTC,pin_name);
			break;
			case DIO_PORTD:
			Set_Bit(PORTD,pin_name);
			break;
			default:
			break;
		}
		break;
		default:
		break;
	}
}

Uint8 DIO_GetPin_Value(Uint8 port_name, Uint8 pin_name)
{
	switch(port_name)
	{
		case DIO_PORTA:
		return Get_Bit(PINA,pin_name);
		break;
		case DIO_PORTB:
		return Get_Bit(PINB,pin_name);
		break;
		case DIO_PORTC:
		return Get_Bit(PINC,pin_name);
		break;
		case DIO_PORTD:
		return Get_Bit(PIND,pin_name);
		break;
		default:
		return 0;
		break;
	}
}

void DIO_TogglePin_Value(Uint8 port_name, Uint8 pin_name)
{
	switch(port_name)
	{
		case DIO_PORTA:
		Toggle_Bit(PORTA,pin_name);
		break;
		case DIO_PORTB:
		Toggle_Bit(PORTB,pin_name);
		break;
		case DIO_PORTC:
		Toggle_Bit(PORTC,pin_name);
		break;
		case DIO_PORTD:
		Toggle_Bit(PORTD,pin_name);
		break;
		default:
		break;
	}
}

void DIO_SetPin_Pullup(Uint8 port_name, Uint8 pin_name)
{
	switch(port_name)
	{
		case DIO_PORTA:
		Set_Bit(PORTA,pin_name);
		break;
		case DIO_PORTB:
		Set_Bit(PORTB,pin_name);
		break;
		case DIO_PORTC:
		Set_Bit(PORTC,pin_name);
		break;
		case DIO_PORTD:
		Set_Bit(PORTD,pin_name);
		break;
		default:
		break;
	}
}