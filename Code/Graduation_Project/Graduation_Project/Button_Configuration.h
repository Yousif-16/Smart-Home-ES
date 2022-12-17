/*
 * Button_Configuration.h
 *
 * Created: 9/8/2022 3:30:59 PM
 *  Author: Dell
 */ 


#ifndef BUTTON_CONFIGURATION_H_
#define BUTTON_CONFIGURATION_H_
#include "../DIO_Driver/DIO.h"

/*-------------Button0-------------*/
#define Button0_Port DIO_PORTB
#define Button0_Pin  PIN_0
#define Button0_INIT_STATE PIN_INTERNAL_PULLUP

/*-------------Button1-------------*/
#define Button1_Port DIO_PORTD
#define Button1_Pin  PIN_6
#define Button1_INIT_STATE PIN_INTERNAL_PULLUP

/*-------------Button2-------------*/
#define Button2_Port DIO_PORTD
#define Button2_Pin  PIN_2
#define Button2_INIT_STATE PIN_INTERNAL_PULLUP

#endif /* BUTTON_CONFIGURATION_H_ */