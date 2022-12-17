#include "Button.h"


Uint8 Init_Button (Uint8 Port_num,Uint8 Pin_num)
{
	Uint8 ret_val=Success_Button;
	if(Port_num>3||Pin_num>7)
	{
		ret_val=Error_Button;
	}
	else
	{
		DIO_SetPin_Value(Port_num, Pin_num,PIN_IN);
	}
	return ret_val;
}
