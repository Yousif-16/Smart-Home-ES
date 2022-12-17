/*
 * ADC.c
 *
 * Created: 9/22/2022 11:51:38 AM
 *  Author: Dell
 */ 
#include "ADC.h"
#include "DC_Motor.h"
#include "Timer.h"
#include <avr/interrupt.h>

 Uint16 Temp = 0;
Uint8 i=1; 
 void ADC_Init(void)
 {
 // Voltage Reference
 ADMUX = (ADC_Volt_Ref << 6) | (ADMUX & 0X3F);
 
 // ADC Right/Left Adjust
 ADMUX = (ADC_Data_Presentation << 5) | (ADMUX & 0XDF);
 
 // ADC Mode
 ADCSRA = (ADC_Cov_Mode << 5) | (ADCSRA & 0XDF);
 
 // ADC: Auto-Triggered Mode
 SFIOR = (ADC_Auto_Triggered_Mode_Type << 5) | (SFIOR & 0X1F);
 
 // ADC Pre_Scaler
 ADCSRA = ADC_CLK | (ADCSRA & 0XF8);
 
 // ADC Interrupt
 SREG |= Global_INT << 7;
 ADCSRA = (ADC_INT << 3) | (ADCSRA & 0XF7);
 
 // ADC Enable or Disable
 ADCSRA = (1 << 7) | (ADCSRA & 0X7F);
 }

 Uint16 ADC_Read(Uint8 pin)
 {
 Uint16 Value = 0;
 ADMUX = pin | (ADMUX & 0XE0);
 ADCSRA = (1 << 6) | (ADCSRA & 0XBF);
 while(!Get_Bit(ADCSRA, 4));
 Value = ADCRA;
 return Value;
 }

 void ADC_Disable(void)
 {
 Clear_Bit(ADCSRA, 7);
 }

 ISR(ADC_vect)
 {
 // Write the ADC handler here
 Temp = ADC_Read(PIN_7);
 if(Temp >= 57)
 DC_Motor1_START(100,Anti_Clock_Wise);
 if(Temp <= 43)
 DC_Motor1_STOP();
 if(i)
 {
	Timer2_Init();
	Timer2_Start();
	Timer2_SetDelay(100);
	i = 0; 
 }
 }
