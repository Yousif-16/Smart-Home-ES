/*
 * EEPROM.c
 *
 * Created: 8/3/2021 4:14:26 PM
 *  Author: ahmed
 */ 

#include "EEPROM.h"
#include <stdlib.h>

#define F_CPU 16000000
#include <util/delay.h>
Uint8 Arr[4]={0};
#define Null           (void*)(0)

void EEPROM_INIT(void)
{
	I2C_INIT();
}

void EEPROM_WriteByte(Uint8 Device_Page, Uint8 Data_Add, Uint8 Data)
{
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	Uint8 Device_Add = 0X50 | Device_Page;
	//Sending start condition
	I2C_SendStartCond();
	//sending slave address with write operation
	I2C_SendSlaveAdd_WriteOP(Device_Add);
	//sending data byte address
	I2C_SendData(Data_Add);
	//sending the data byte
	I2C_SendData(Data);
	//Sending stop condition
	I2C_SendStopCond();
	_delay_ms(10);
}

void EEPROM_WriteMultiBytes(Uint8 Device_Page, Uint8 Data_Add, Uint8* Data, Uint8 Data_Size)
{
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	Uint8 Device_Add = 0X50 | Device_Page;
	//Sending start condition
	I2C_SendStartCond();
	//sending slave address with write operation
	I2C_SendSlaveAdd_WriteOP(Device_Add);
	//sending data byte address
	I2C_SendData(Data_Add);
	//sending the data byte
	I2C_SendMultiData(Data, Data_Size);
	//Sending stop condition
	I2C_SendStopCond();	
	_delay_ms(10);
}
void EEPROM_WriteString(Uint8 Device_Page, Uint8 Data_Add, Uint8* Data)
{
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	Uint8 Device_Add = 0X50 | Device_Page;
	//Sending start condition
	I2C_SendStartCond();
	//sending slave address with write operation
	I2C_SendSlaveAdd_WriteOP(Device_Add);
	//sending data byte address
	I2C_SendData(Data_Add);
	//sending the data byte
	I2C_SendString(Data);
	//Sending stop condition
	I2C_SendStopCond();	
	_delay_ms(10);
}


Uint8 EEPROM_ReadByte(Uint8 Device_Page, Uint8 Data_Add)
{
	Uint8 Data = 0;
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	Uint8 Device_Add = 0X50 | Device_Page;
	//Sending start condition
	I2C_SendStartCond();
	//sending slave address with write operation
	I2C_SendSlaveAdd_WriteOP(Device_Add);
	//sending data byte address
	I2C_SendData(Data_Add);
	
	//Sending repeated start condition
	I2C_SendRepStartCond();
	//sending slave address with read operation
	I2C_SendSlaveAdd_ReadOP(Device_Add);	
	//Receiving the data byte
	Data = I2C_ReadData();
	//Sending stop condition
	I2C_SendStopCond();	
	
	return Data;
}
void EEPROM_ReadMultiByte(Uint8 Device_Page, Uint8 Data_Add, Uint8* Rec_Loc, Uint8 Data_Size)
{
	Uint8 i;
	if (Device_Page > 7)
	Device_Page = 7;
	//Device address calculation
	Uint8 Device_Add = 0X50 | Device_Page;
	//Sending start condition
	I2C_SendStartCond();
	//sending slave address with write operation
	I2C_SendSlaveAdd_WriteOP(Device_Add);
	//sending data byte address
	I2C_SendData(Data_Add);
	
	//Sending repeated start condition
	I2C_SendRepStartCond();
	//sending slave address with read operation
	I2C_SendSlaveAdd_ReadOP(Device_Add);
	//Receiving the data byte
	for (i = 0; i < Data_Size; i++)
	{
		Rec_Loc[i] = I2C_ReadMultiData();
	}
	//Sending stop condition
	I2C_SendStopCond();
}
Uint8 EEPROM_Search(Uint8 Page, Uint8 *User_Name, Uint8 Counter_4)
{
   for (Uint8 z=0;z<Counter_4;z++)
   {
	   if ((EEPROM_ReadByte(Page,z) == User_Name[0])  && (EEPROM_ReadByte(Page,z+1) == User_Name[1]) &&  (EEPROM_ReadByte(Page,z+2) == User_Name[2]) && (EEPROM_ReadByte(Page,z+3) == User_Name[3]))
	   {
		   UART_TX_Str("\r\n");
		   UART_TX_Str("Found");
		   Arr[0]=z;
		   Arr[1]=z+1;
		   Arr[2]=z+2;
		   Arr[3]=z+3;
		   return 1;
		   break;
	   }	   
   }
   return 0;
   	
	
}
Uint8 EEPROM_Delete(Uint8 Page,Uint8 Page_Pass, Uint8 *User_Name, Uint8 Counter_1 )

{
	if (EEPROM_Search(Page,User_Name,Counter_1))
	{
		EEPROM_WriteByte(Page,Arr[0],255);
		EEPROM_WriteByte(Page,Arr[1],255);
		EEPROM_WriteByte(Page,Arr[2],255);
		EEPROM_WriteByte(Page,Arr[3],255);
		EEPROM_WriteByte(Page_Pass,Arr[0],255);
		EEPROM_WriteByte(Page_Pass,Arr[1],255);
		EEPROM_WriteByte(Page_Pass,Arr[2],255);
		EEPROM_WriteByte(Page_Pass,Arr[3],255);
		UART_TX_Str("Deleted\r\n");
	}
	else
	{
		UART_TX_Str("User Name Not Found");
	}
	
}
void EEPROM_Reset(void)
{
	for (int i=0;i<=7;i++)
	{
		for(int j=0;j<=255;j++)
		{
			EEPROM_WriteByte(i,j,255);
		}
	}
}