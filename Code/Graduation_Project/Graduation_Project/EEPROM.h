/*
 * EEPROM.h
 *
 * Created: 8/3/2021 4:14:42 PM
 *  Author: ahmed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C.h"
#define Page_User_Name    0
#define Page_Password     1
#define Page_User_Name_KeyPad  2
#define Page_Password_KeyPad     3
void EEPROM_INIT(void);

void EEPROM_WriteByte(Uint8 Device_Page, Uint8 Data_Add, Uint8 Data);
void EEPROM_WriteMultiBytes(Uint8 Device_Page, Uint8 Data_Add, Uint8* Data, Uint8 Data_Size);
void EEPROM_WriteString(Uint8 Device_Page, Uint8 Data_Add, Uint8* Data);

Uint8 EEPROM_ReadByte(Uint8 Device_Page, Uint8 Data_Add);
void EEPROM_ReadMultiByte(Uint8 Device_Page, Uint8 Data_Add, Uint8* Rec_Loc, Uint8 Data_Size);
Uint8 EEPROM_Search(Uint8 Page, Uint8 *User_Name, Uint8 Counter_4);
Uint8 EEPROM_Delete(Uint8 Page,Uint8 Page_Pass, Uint8 *User_Name, Uint8 Counter_1 );
void EEPROM_Reset(void);


#endif /* EEPROM_H_ */