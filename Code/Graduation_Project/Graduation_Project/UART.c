/*
 * UART.c
 *
 * Created: 9/29/2022 1:02:18 PM
 *  Author: Dell
 */ 
#include "UART.h"
#include "LCD.h"
#include <avr/interrupt.h>
Uint8 Var=0;
void UART_Init(void)
{
	// Global Interrupt
	SREG |= Global_INT << 7;
	
	// Peripheral Interrupt
	UCSRB = (UART_TX_INT << 6) | (UART_RX_INT << 7) | (UCSRB & 0X3F);
	
	// TX Pin Direction
	DIO_SetPin_Dir(DIO_PORTD, PIN_1, PIN_OUT);
	
	// RX Pin Direction
	DIO_SetPin_Dir(DIO_PORTD, PIN_0, PIN_IN);
	
	// UART Receiver/ Transmitter Enable
	UCSRB = (1 << 3) | (1 << 4) | (UCSRB & 0X3F);
	
	// UART Doubled Speed Mode
	UCSRA = (UART_Doubled_Speed << 1) | (UCSRA & 0XFD);
	
	// Parity Bit Mode
	// Data Bits Mode
	// Stop Bit  Mode
	UCSRC = (1 << 7) | (UART_Data_Bits << 1) | (UART_Stop_Bits << 3) | (UART_Parity_Mode << 4) | (UCSRC & 0X41);
	
	// UART Baud Rate
	UBRRL = (Uint8)UART_Baud_Rate;
	UBRRH = (UART_Baud_Rate >> 8);
}

void UART_TX_Char(Uint8 data)
{
	// Sending Data
	UDR = data;
	
	// Checking the data is sent
	while(!Get_Bit(UCSRA, 5));
}

void UART_TX_Str(Uint8 *str)
{
	for(Uint8 i = 0; str[i] != '\n'; i++)
	{
		UART_TX_Char(str[i]);
	}
}

Uint8 UART_RX_Char(void)
{
	Uint8 Value = 0;
	while(!Get_Bit(UCSRA, 5));
	Value = UDR;
	return Value;
}
/*
void UART_receiveString(Uint8 *Str)
{
	Uint8 i = 0;
*/
	/* Receive the first byte */	
/*	
	Str[i] = UART_RX_Char();
*/
	/* Receive the whole string until the '#' */
/*	
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_RX_Char();
	}
*/
	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
/*	
	Str[i] = '\0';

}
*/


ISR(USART_RXC_vect)
{		
	UART_TX_Str("test1");
}

ISR(USART_TXC_vect)
{
	// Write UART transmit handler here
	
}