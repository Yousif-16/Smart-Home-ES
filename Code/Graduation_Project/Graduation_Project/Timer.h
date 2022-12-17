/*
 * Timer.h
 *
 * Created: 9/23/2022 8:01:04 PM
 *  Author: Dell
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "Timer_Configuration.h"

/*----------------------------------------------------------------Timer0---------------------------------------------------------------*/
// Timer0 Modes
#define Timer0_OVF 0
#define Timer0_P_PWM 1
#define Timer0_CTC 2
#define Timer0_F_PWM 3

// Timer0 Clocks
#define Timer0_No_CLK 0
#define Timer0_Freq_1 1
#define Timer0_Freq_8 2
#define Timer0_Freq_64 3
#define Timer0_Freq_256 4
#define Timer0_Freq_1024 5

// Timer0 Pre_Scaler Divider
#define Timer0_Freq_Div_1 1
#define Timer0_Freq_Div_8 8
#define Timer0_Freq_Div_64 64
#define Timer0_Freq_Div_256 256
#define Timer0_Freq_Div_1024 1024

// Timer0 Fast PWM Mode
#define F_OC0_C_Comp_S_TOP 2
#define F_OC0_S_Comp_C_TOP 3 

// Timer0 Phase PWM Mode
#define P_OC0_C_CompU_S_CompD 2
#define P_OC0_S_CompU_C_CompD 3

void Timer0_Init(void);
void Timer0_SetDelay(Uint32 delay_ms);
void PWM0_Gen(f32 Duty_Cycle);
void Timer0_Start(void);
void Timer0_Stop(void);

/*----------------------------------------------------------------Timer1---------------------------------------------------------------*/
// Timer1 Modes
#define Timer1_OVF 0
#define Timer1_P_PWM_ICR1 1
#define Timer1_CTC 2
#define Timer1_F_PWM 3

// Timer1 Clocks
#define Timer1_No_CLK 0
#define Timer1_Freq_1 1
#define Timer1_Freq_8 2
#define Timer1_Freq_64 3
#define Timer1_Freq_256 4
#define Timer1_Freq_1024 5

// Timer1 Pre_Scaler Divider
#define Timer1_Freq_Div_1 1
#define Timer1_Freq_Div_8 8
#define Timer1_Freq_Div_64 64
#define Timer1_Freq_Div_256 256
#define Timer1_Freq_Div_1024 1024

// Timer1 Fast PWM Mode
#define F_OC1A_Disconnected 0
#define F_OC1A_Reserved 1
#define F_OC1A_C_Comp_S_TOP 2
#define F_OC1A_S_Comp_C_TOP 3

#define F_OC1B_Disconnected 0
#define F_OC1B_Reserved 1
#define F_OC1B_C_Comp_S_TOP 2
#define F_OC1B_S_Comp_C_TOP 3

// Timer1 Phase PWM Mode
#define P_OC1A_Disconnected 0
#define P_OC1A_Reserved 1
#define P_OC1A_C_CompU_S_CompD 2
#define P_OC1A_S_CompU_C_CompD 3

#define P_OC1B_Disconnected 0
#define P_OC1B_Reserved 1
#define P_OC1B_C_CompU_S_CompD 2
#define P_OC1B_S_CompU_C_CompD 3

void Timer1_Init(void);
void Timer1_SetDelay(Uint32 delay_ms_A, Uint32 delay_ms_B);
void PWM1_Gen(f32 Duty_Cycle_A, f32 Duty_Cycle_B, f32 F_OC1_AB_KHz);
void Timer1_Start(void);
void Timer1_Stop(void);


/*----------------------------------------------------------------Timer2---------------------------------------------------------------*/
// Timer2 Modes
#define Timer2_OVF 0
#define Timer2_P_PWM 1
#define Timer2_CTC 2
#define Timer2_F_PWM 3

// Timer2 Clocks
#define Timer2_No_CLK 0
#define Timer2_Freq_1 1
#define Timer2_Freq_8 2
#define Timer2_Freq_32 3
#define Timer2_Freq_64 4
#define Timer2_Freq_128 5
#define Timer2_Freq_256 6
#define Timer2_Freq_1024 7

// Timer2 Pre_Scaler Divider
#define Timer2_Freq_Div_1 1
#define Timer2_Freq_Div_8 8
#define Timer2_Freq_Div_32 32
#define Timer2_Freq_Div_64 64
#define Timer2_Freq_Div_128 128
#define Timer2_Freq_Div_256 256
#define Timer2_Freq_Div_1024 1024

// Timer2 Fast PWM Mode
#define F_OC2_C_Comp_S_TOP 2
#define F_OC2_S_Comp_C_TOP 3

// Timer2 Phase PWM Mode
#define P_OC2_C_CompU_S_CompD 2
#define P_OC2_S_CompU_C_CompD 3

void Timer2_Init(void);
void Timer2_SetDelay(Uint32 delay_ms);
void PWM2_Gen(f32 Duty_Cycle);
void Timer2_Start(void);
void Timer2_Stop(void);


#endif /* TIMER_H_ */