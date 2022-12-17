/*
 * ALARM.c
 *
 * Created: 11/11/2022 7:24:56 PM
 *  Author: Candle-Store
 */ 
#include "ALARM.h"
#include "Buzzer.h"
#include "LED.h"


#include <util/delay.h>


#define D 1000

void ALARM_ON(void)

{
	
	LED0_Toggle();
	_delay_ms(D);
	LED2_Toggle();
	_delay_ms(D);
	LED4_Toggle();
	Buzzer_Toggle();
	_delay_ms(D);
	
	LED0_OFF();
	LED2_OFF();
	LED4_OFF();
	Buzzer_OFF();
	
	LED1_Toggle();
	_delay_ms(D);
	LED3_Toggle();
	Buzzer_Toggle();
	_delay_ms(D);
	
	LED1_OFF();
	LED3_OFF();
	Buzzer_OFF();
}
