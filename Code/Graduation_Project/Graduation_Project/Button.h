#ifndef BUTTON_H_
#define BUTTON_H_
#include "DIO.h"

#define Success_Button 0
#define Error_Button   1

typedef enum
{
	Button_PORTA,Button_PORTB,Button_PORTC,Button_PORTD
}En_Button_Ports;

Uint8 Init_Button (Uint8 Port_num,Uint8 Pin_num);





#endif
