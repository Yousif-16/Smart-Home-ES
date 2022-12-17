/*
 * I2C.c
 *
 * Created: 7/31/2021 6:31:18 PM
 *  Author: ahmed
 */ 

/*
Generic I2C Driver to send / receive single Byte or Multiple Bytes
in I2C four modes:
Master Transmitter (MT)
Master Receiver (MR)
Slave Transmitter (ST)
Slave Receiver (SR)
*/

#define F_CPU 16000000
#include <util/delay.h>

#include "I2C.h"
#include <avr/interrupt.h>

#define Null           (void*)(0)

/* Test Strings:
   - Those strings are used to test the success
     of every stage of the I2C communication
     between the Micro-controller and EEPROM
   - To use these strings all you have to do is
     to uncomment all the LCD writeSTRING function	 
	 and put these two callback functions in main
	 function!
	 	I2C_callback0(LCD_Clear);
	 	I2C_callback1(LCD_WriteSTRING); 
*/
Uint8 string1[] = "E-Start Cond";
Uint8 string2[] = "E-Rep Start Cond";
Uint8 string3[] = "E-Slave Add W-OP";
Uint8 string4[] = "E-Slave Add R-OP";
Uint8 string5[] = "E-Send Data";
Uint8 string6[] = "E-Receive Data";

Uint8 string11[] = "Start cond sent";
Uint8 string12[] = "Rep Start sent";
Uint8 string13[] = "Slave & W sent";
Uint8 string14[] = "Slave & R sent";
Uint8 string15[] = "Data sent";
Uint8 string16[] = "Data received";




void (*pptr0)() = Null;
void (*pptr1)(Uint8 *) = Null;

/*Implementation of call back functions*/
void I2C_callback0(void(*p)())
{
	pptr0 = p;
}
void I2C_callback1(void(*p)(Uint8 *))
{
	pptr1 = p;
}
void I2C_INIT(void)
{	
	/*Global Interrupt*/
	SREG = Global_INT << 7;
	
	//Peripheral Interrupt
	TWCR = (1<<TWEN)|(I2C_INT<<TWIE);
			
	//Frequency generation
	TWBR = 12;
	TWSR = 0X00;  //Pre-scaler value (1)
	//TWBR = ((16000 / I2C_MASTER_CLOCK) - 16) / 2;
	
}

void I2C_SendStartCond(void)
{
	/*Sending Start condition*/
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != TRANS_START_COND)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string1);
// 		_delay_ms(2000);
// 	}
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string11);	
// 	}
}
void I2C_SendRepStartCond(void)
{
	/*Sending Repeated Start condition*/
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != TRANS_REP_START_COND)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string2);		
// 		_delay_ms(2000);
// 	}	
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string12);
// 	}	
}

void I2C_SendSlaveAdd_WriteOP(Uint8 SLA_Add)
{
	TWDR = SLA_Add<<1;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != TRANS_SLA_W_REC_ACK)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string3);	
// 		_delay_ms(2000);	
// 	}	
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string13);
// 	}	
	_delay_ms(100);
}
void I2C_SendSlaveAdd_ReadOP(Uint8 SLA_Add)
{
	TWDR = (SLA_Add<<1) | (0X01);
	TWCR = (1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != TRANS_SLA_R_REC_ACK)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string4);	
// 		_delay_ms(2000);	
// 	}	
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string14);
// 	}	
}

void I2C_SendData(Uint8 Data)
{
	TWDR = Data;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != M_TRANS_DATA_REC_ACK)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string5);	
// 		_delay_ms(2000);	
// 	}	
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string15);
// 	}	
}
void I2C_SendMultiData(Uint8* Data, Uint8 Data_Size)
{
	Uint8 i = 0;
	for (i = 0; i < Data_Size; i++)
	{
		I2C_SendData(Data[i]);
	}
}
void I2C_SendString(Uint8* Data)
{
	Uint8 i = 0;
	while (Data[i] != '\0')
	{
		I2C_SendData(Data[i]);
		i++;
	}
}

Uint8 I2C_ReadData(void)
{
	TWCR = (1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != M_REC_DATA_TRANS_NACK)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string6);	
// 		_delay_ms(2000);	
// 	}	
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string16);
// 	}	
	return TWDR;
}
Uint8 I2C_ReadMultiData(void)
{
	TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
// 	if((TWSR & 0XF8) != M_REC_DATA_TRANS_ACK)
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string6);
// 		_delay_ms(2000);
// 	}
// 	else
// 	{
// 		(*pptr0)();
// 		(*pptr1)(string16);
// 	}
	return TWDR;
}

void I2C_SendStopCond(void)
{
	TWCR = (1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
	Set_Bit(TWCR, 7);
	//while (!(TWCR & (1<<TWINT))); //Polling on interrupt flag until the flag is raised up
}

