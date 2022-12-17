/*
 * UART.h
 *
 * Created: 9/29/2022 1:01:26 PM
 *  Author: Dell
 */ 


#ifndef UART_H_
#define UART_H_
#include "UART_Configuration.h"
#include "EEPROM.h"

// UART Parity Modes
#define Parity_Disabled 0
#define Parity_Reserved 1
#define Parity_Enabled_Even 2
#define Parity_Enabled_Odd 3

// UART Data Bits
#define Data_5_Bits 0
#define Data_6_Bits 1
#define Data_7_Bits 2
#define Data_8_Bits 3

// UART Stop Bits
#define Stop_1_Bits 0
#define Stop_2_Bits 1

// UART Baud Rate
#define B_2400 832
#define B_4800 416
#define B_9600 207
#define B_14400 138
#define B_19200 103
#define B_28800 68
#define B_38400 51
#define B_57600 34
#define B_76800 25
#define B_115000 16
#define B_234000 8
#define B_250000 7
#define B_501000 3
#define B_1000000 1

//UART Doubled Speed Mode
#define Doubled_Speed_Disbaled 0
#define Doubled_Speed_Enbaled 1

// UART Functions
void UART_Init(void);
void UART_TX_Char(Uint8 data);
void UART_TX_Str(Uint8 *str);
Uint8 UART_RX_Char(void);
void UART_receiveString(Uint8 *Str);
void UART_init(Uint32 baud_rate);



#endif /* UART_H_ */