/*
 * ADC.h
 *
 * Created: 9/22/2022 11:50:55 AM
 *  Author: Dell
 */ 

#ifndef ADC_H_
#define ADC_H_
#include "ADC_Configuration.h"

// ADC Pins
#define ADC_PIN0 0
#define ADC_PIN1 1
#define ADC_PIN2 2
#define ADC_PIN3 3
#define ADC_PIN4 4
#define ADC_PIN5 5
#define ADC_PIN6 6
#define ADC_PIN7 7

// Voltage Reference
#define ADC_AREF 0
#define ADC_AVCC 1
#define ADC_Reserved 2
#define ADC_Internal_2_56 3

// Clock Sources
#define ADC_CLK_2 0
#define ADC_CLK_2_2 1
#define ADC_CLK_4 2
#define ADC_CLK_8 3
#define ADC_CLK_16 4
#define ADC_CLK_32 5
#define ADC_CLK_64 6
#define ADC_CLK_128 7

// ADC Mode
#define Single_Conv_Mode 0
#define Auto_Triggered_Mode 1

// Types of Auto Triggered Mode
#define Free_Running 0
#define Analog_Comparator 1
#define External_Interrupt_Requset 2
#define Timer_Counter0_Comp_Match 3
#define Timer_Counter0_Overflow 4
#define Timer_Counter_Comp_Match_B 5
#define Timer_Counter1_Overflow 6
#define Timer_Counter1_Capture_Event 7

// ADC Right/Left Adjust Modes
#define ADC_Right_Adjust 0
#define ADC_Left_Adjust 1

void ADC_Init(void);
Uint16 ADC_Read(Uint8 pin);
void ADC_Disable(void);

#endif /* ADC_H_ */