/*
 * Timer_Configuration.h
 *
 * Created: 9/23/2022 8:01:31 PM
 *  Author: Dell
 */ 


#ifndef TIMER_CONFIGURATION_H_
#define TIMER_CONFIGURATION_H_
#include "DIO.h"
#include "Interrupt.h"

/*----------------------------------------------------------------Timer0---------------------------------------------------------------*/
// Timer0 Selected Mode
#define Timer0_Mode Timer0_P_PWM
// Timer0 Selected Clock
#define Timer0_CLK Timer0_Freq_1024
// Timer0 Selected Frequency Divider
#define Timer0_Freq_Divider Timer0_Freq_Div_1024
// Timer0 Fast PWM Selected Mode
#define  F_PWM0_Mode F_OC0_C_Comp_S_TOP
// Timer0 Phase PWM Selected Mode
#define  P_PWM0_Mode P_OC0_C_CompU_S_CompD

/*----------------------------------------------------------------Timer1---------------------------------------------------------------*/
// Timer1 Selected Mode
#define Timer1_Mode Timer1_OVF
// Timer1 Selected Clock
#define Timer1_CLK Timer1_Freq_1024
// Timer1 Selected Frequency Divider
#define Timer1_Freq_Divider Timer1_Freq_Div_1024
// Timer1 Fast PWM Selected Mode
#define  F_OC1A_Mode F_OC1A_C_Comp_S_TOP
// Timer1 Phase PWM Selected Mode
#define  P_OC1A_Mode P_OC1A_C_CompU_S_CompD
// Timer1 Fast PWM Selected Mode
#define  F_OC1B_Mode F_OC1B_C_Comp_S_TOP
// Timer1 Phase PWM Selected Mode
#define  P_OC1B_Mode P_OC1B_C_CompU_S_CompD

/*----------------------------------------------------------------Timer2---------------------------------------------------------------*/
// Timer2 Selected Mode
#define Timer2_Mode Timer2_CTC
// Timer2 Selected Clock
#define Timer2_CLK Timer2_Freq_1024
// Timer2 Selected Frequency Divider
#define Timer2_Freq_Divider Timer2_Freq_Div_1024
// Timer2 Fast PWM Selected Mode
#define  F_PWM2_Mode F_OC2_C_Comp_S_TOP
// Timer2 Phase PWM Selected Mode
#define  P_PWM2_Mode P_OC2_C_CompU_S_CompD

// Micro_Controller Internal Frequency
#define MC_Freq_MHz 16 

#endif /* TIMER_CONFIGURATION_H_ */