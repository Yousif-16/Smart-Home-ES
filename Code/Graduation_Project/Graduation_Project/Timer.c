/*
 * Timer.c
 *
 * Created: 9/23/2022 8:02:20 PM
 *  Author: Dell
 */ 
#include "Timer.h"
#include "LCD.h"
#include <avr/interrupt.h>

Uint16 Timer0_Num_OVF = 0;
Uint8 Timer0_Init_Value = 0;
Uint16 Timer1A_Num_OVF = 0;
Uint8 Timer1A_Init_Value = 0;
Uint16 Timer1B_Num_OVF = 0;
Uint8 Timer1B_Init_Value = 0;
Uint16 Timer2_Num_OVF = 0;
Uint8 Timer2_Init_Value = 0;

/*------------------------------------>Timer0<-----------------------------------------------*/
void Timer0_Init(void)
{
	// Global Interrupt
	SREG |= Global_INT << 7;
	
	// Timer0_Modes
	#if Timer0_Mode == Timer0_OVF
		Clear_Bit(TCCR0, 3);
		Clear_Bit(TCCR0, 6);
	
	// Timer0_Perpheral Interrupt Enable/Disable
		TIMSK = (Timer0_OVF_INT) | (TIMSK & 0XFE);
	
	#elif Timer0_Mode == Timer0_P_PWM
		Clear_Bit(TCCR0, 3);
		Set_Bit(TCCR0, 6);
	
	// Phase_PWM Mode
		TCCR0 = (P_PWM0_Mode << 4) | (TCCR0 & 0XCF);
	
	// Timer0_Perpheral Interrupt Enable/Disable
	TIMSK = (Timer0_OVF_INT) | (TIMSK & 0XFE);
	
	// OC0 Pin direction
		DIO_SetPin_Dir(DIO_PORTB, PIN_3, PIN_OUT);
	
	#elif Timer0_Mode == Timer0_CTC
		Set_Bit(TCCR0, 3);
		Clear_Bit(TCCR0, 6);
	
	// Timer0_Perpheral Interrupt Enable/Disable
		TIMSK = (Timer0_CTC_INT << 1) | (TIMSK & 0XFD);
	
	#elif Timer0_Mode == Timer0_F_PWM
		Set_Bit(TCCR0, 3);
		Set_Bit(TCCR0, 6);
	
	// Fast_PWM Mode
		TCCR0 = (F_PWM0_Mode << 4) | (TCCR0 & 0XCF);
	
	// Timer0_Perpheral Interrupt Enable/Disable
	TIMSK = (Timer0_OVF_INT) | (TIMSK & 0XFE);
	
	// OC0 Pin direction
		DIO_SetPin_Dir(DIO_PORTB, PIN_3, PIN_OUT);
	
	#endif
}

void Timer0_SetDelay(Uint32 delay_ms)
{
	Uint8 Tick_Time_us = 0;
	Uint32 Tick_num = 0;
	Tick_Time_us = Timer0_Freq_Divider / MC_Freq_MHz;
	Tick_num = (delay_ms*1000) / Tick_Time_us;
    
	#if Timer0_Mode == Timer0_OVF 
 		if(Tick_num <= 256)
		{ 
			Timer0_Init_Value = 256 - Tick_num;
			TCNT0 = Timer0_Init_Value;
			Timer0_Num_OVF = 1;
		}
		else
		{
			Timer0_Num_OVF = !(Tick_num % 256) ? (Tick_num / 256) : (Tick_num / 256) + 1;
			Timer0_Init_Value = 256 - (Tick_num % 256);
			TCNT0 = Timer0_Init_Value;
		}
	#elif Timer0_Mode == Timer0_CTC 
		if(Tick_num <= 256)
		{
			Timer0_Init_Value = Tick_num - 1;
			OCR0 = Timer0_Init_Value;
			Timer0_Num_OVF = 1;
		}
		else
		{
			Timer0_Num_OVF = !(Tick_num % 256) ? (Tick_num / 256) : (Tick_num / 256) + 1;
			Timer0_Init_Value = (Tick_num % 256) - 1;
			OCR0 = Timer0_Init_Value;
		}
	
	#endif
}

void PWM0_Gen(f32 Duty_Cycle)
{
	if(Duty_Cycle < 0)
		Duty_Cycle = 0;
	else if(Duty_Cycle > 100)
		Duty_Cycle = 100;	
	
	#if Timer0_Mode == Timer0_F_PWM
		#if F_PWM0_Mode == F_OC0_C_Comp_S_TOP
			OCR0 = !Duty_Cycle? 0 : ((Duty_Cycle / 100) * 256) - 1;
		
		#elif F_PWM0_Mode == F_OC0_S_Comp_C_TOP
			OCR0 = Duty_Cycle == 100? 0 : 255 - ((Duty_Cycle / 100) * 256);
		
		#endif	
	#elif Timer0_Mode == Timer0_P_PWM
		#if P_PWM0_Mode == P_OC0_C_CompU_S_CompD
			OCR0 = Duty_Cycle * 255 / 100;
		
		#elif P_PWM0_Mode == P_OC0_S_CompU_C_CompD
			OCR0 = 255 - (Duty_Cycle * 255 / 100);
		
		#endif
	#endif
}

void Timer0_Start(void)
{
	TCCR0 = (Timer0_CLK) | (TCCR0 & 0XF8);
}
void Timer0_Stop(void)
{
	TCCR0 &= 0XF8;
}

ISR(TIMER0_OVF_vect)
{
	static Uint32 Count = 0;
	Count++;
	if(Timer0_Num_OVF == Count)
	{
		// Write OVF of Timer_0 handler here
		
		Timer0_Stop();	
		Count = 0;
		TCNT0 = Timer0_Init_Value;
	}
	
}

ISR(TIMER0_COMP_vect)
{
	static Uint32 Count = 0;
	Count++;
	if(Count == 1 && Timer0_Num_OVF == Count)
	{
		// Write CMP of Timer_0 handler here
			
			
		Count = 0;
		OCR0 = Timer0_Init_Value;
	}
	else if(Count == 1)
		OCR0 = 255;	
	else if(Timer0_Num_OVF == Count)
	{
		// Write CMP of Timer_0 handler here
		
		
		Count = 0;
		OCR0 = Timer0_Init_Value;
	}
}

/*------------------------------------>Timer1<-----------------------------------------------*/
void Timer1_Init(void)
{
	// Global Interrupt
	SREG |= Global_INT << 7;
	
	// Timer1_Modes
	#if Timer1_Mode == Timer1_OVF
	// TCCR1A Register
	Clear_Bit(TCCR1A, 0);
	Clear_Bit(TCCR1A, 1);
	// TCCR1B Register
	Clear_Bit(TCCR1B, 3);
	Clear_Bit(TCCR1B, 4);
	
	// Timer1_Perpheral Interrupt Enable/Disable
	TIMSK = (Timer1_OVF_INT << 2) | (TIMSK & 0XFB);
	
	#elif Timer1_Mode == Timer1_P_PWM_ICR1
	// TCCR1A Register
	Clear_Bit(TCCR1A, 0);
	Set_Bit(TCCR1A, 1);
	// TCCR1B Register
	Clear_Bit(TCCR1B, 3);
	Set_Bit(TCCR1B, 4);
	
	// Phase_PWM Mode
	TCCR1A = (P_OC1A_Mode << 6) | (P_OC1A_Mode << 4) |(TCCR1A & 0X0F);
	
	// Timer1_Perpheral Interrupt Enable/Disable
	TIMSK = (Timer1_OVF_INT << 2) | (TIMSK & 0XFB);
	TIMSK = (Timer1_CTCA_INT << 4) | (Timer1_CTCB_INT << 3) | (TIMSK & 0XE7);
	
	// OC1 Pin direction
	DIO_SetPin_Dir(DIO_PORTD, PIN_5, PIN_OUT);
	DIO_SetPin_Dir(DIO_PORTD, PIN_4, PIN_OUT);
	
	#elif Timer1_Mode == Timer1_CTC
	// TCCR1A Register
	Clear_Bit(TCCR1A, 0);
	Clear_Bit(TCCR1A, 1);
	// TCCR1B Register
	Set_Bit(TCCR1B, 3);
	Clear_Bit(TCCR1B, 4);
	
	// Timer1_Perpheral Interrupt Enable/Disable
	TIMSK = (Timer1_CTCA_INT << 4) | (Timer1_CTCB_INT << 3) | (TIMSK & 0XE7);
	
	#elif Timer1_Mode == Timer1_F_PWM
	// TCCR1A Register
	Clear_Bit(TCCR1A, 0);
	Set_Bit(TCCR1A, 1);
	// TCCR1B Register
	Set_Bit(TCCR1B, 3);
	Set_Bit(TCCR1B, 4);
	
	// Fast_PWM Mode
	TCCR1A = (F_OC1A_Mode << 6) | (F_OC1B_Mode << 4) |(TCCR1A & 0X0F);
	
	// Timer1_Perpheral Interrupt Enable/Disable
	TIMSK = (Timer1_OVF_INT << 2) | (TIMSK & 0XFB);
	TIMSK = (Timer1_CTCA_INT << 4) | (Timer1_CTCB_INT << 3) | (TIMSK & 0XE7);
	// OC1 Pin direction
	DIO_SetPin_Dir(DIO_PORTD, PIN_5, PIN_OUT);
	DIO_SetPin_Dir(DIO_PORTD, PIN_4, PIN_OUT);
	
	#endif
}

void Timer1_SetDelay(Uint32 delay_ms_A, Uint32 delay_ms_B)
{
	// Tick Time & Tick nums
	Uint8 Tick_Time_us = 0;
	
	Uint32 Tick_num_A = 0;
	Uint32 Tick_num_B = 0;
	
	Tick_Time_us = Timer1_Freq_Divider / MC_Freq_MHz;
	
	Tick_num_A = (delay_ms_A*1000) / Tick_Time_us;
	Tick_num_B = (delay_ms_B*1000) / Tick_Time_us;
	
	#if Timer1_Mode == Timer1_OVF
	if(Tick_num_A <= 65535)
	{
		Timer1A_Init_Value = 65535 - Tick_num_A;
		TCNT1 = Timer1A_Init_Value;
		Timer1A_Num_OVF = 1;
	}
	else
	{
		Timer1A_Num_OVF = !(Tick_num_A % 65535) ? (Tick_num_A / 65535) : (Tick_num_A / 65535) + 1;
		Timer1A_Init_Value = 65535 - (Tick_num_A % 65535);
		TCNT1 = Timer1A_Init_Value;
	}
	#elif Timer1_Mode == Timer1_CTC
	if(Tick_num_A <= 65535)
	{
		Timer1A_Init_Value = Tick_num_A - 1;
		OCR1A = Timer1A_Init_Value;
		Timer1A_Num_OVF = 1;

	}
	else
	{
		Timer1A_Num_OVF = !(Tick_num_A % 65535) ? (Tick_num_A / 65535) : (Tick_num_A / 65535) + 1;
		Timer1A_Init_Value = (Tick_num_A % 65535) - 1;
		OCR1A = Timer1A_Init_Value;
	}
	
	if(Tick_num_B <= 65535)
	{
		Timer1B_Init_Value = Tick_num_B - 1;
		OCR1B = Timer1B_Init_Value;
		Timer1B_Num_OVF = 1;

	}
	else
	{
		Timer1B_Num_OVF = !(Tick_num_B % 65535) ? (Tick_num_B / 65535) : (Tick_num_B / 65535) + 1;
		Timer1B_Init_Value = (Tick_num_B % 65535) - 1;
		OCR1B = Timer1B_Init_Value;
	}
	
	#endif
}

void PWM1_Gen(f32 Duty_Cycle_A, f32 Duty_Cycle_B, f32 F_OC1_AB_KHz)
{
	
	ICR1 = (MC_Freq_MHz * 1000) / (Timer1_Freq_Divider * F_OC1_AB_KHz);
	 
	if(Duty_Cycle_A < 0)
	Duty_Cycle_A = 0;
	else if(Duty_Cycle_A > 100)
	Duty_Cycle_A = 100;
	
	if(Duty_Cycle_B < 0)
	Duty_Cycle_B = 0;
	else if(Duty_Cycle_B > 100)
	Duty_Cycle_B = 100;
	
	#if Timer1_Mode == Timer1_F_PWM
	#if F_OC1A_Mode == F_OC1A_C_Comp_S_TOP
	OCR1A = !Duty_Cycle_A? 0 : ((Duty_Cycle_A / 100) * (ICR1-1)) - 1;
	
	#elif F_OC1A_Mode == F_OC1A_S_Comp_C_TOP
	OCR1A = Duty_Cycle_A == 100? 0 : ICR1 - ((Duty_Cycle_A / 100) * (ICR1-1));
	
	#endif
	
	#if F_OC1B_Mode == F_OC1B_C_Comp_S_TOP
	OCR1B = !Duty_Cycle_B? 0 : ((Duty_Cycle_B / 100) * (ICR1-1)) - 1;
	
	#elif F_OC1B_Mode == F_OC1B_S_Comp_C_TOP
	OCR1B = Duty_Cycle_B == 100? 0 : ICR1 - ((Duty_Cycle_B / 100) * (ICR1-1));
	
	#endif
	
	#elif Timer1_Mode == Timer1_P_PWM_ICR1
	#if P_OC1A_Mode == P_OC1A_C_CompU_S_CompD
	OCR1A = Duty_Cycle_A * ICR1 / 100;
	
	#elif P_OC1A_Mode == P_OC1A_S_CompU_C_CompD
	OCR1A = ICR1 - (Duty_Cycle_A * ICR1 / 100);

	#endif
	
	#if P_OC1B_Mode == P_OC1B_C_CompU_S_CompD
	OCR1B = Duty_Cycle_B * ICR1 / 100;
	
	#elif P_OC1B_Mode == P_OC1B_S_CompU_C_CompD
	OCR1B = ICR1 - (Duty_Cycle_B * ICR1 / 100);

	#endif
	#endif
}

void Timer1_Start(void)
{
	TCCR1B = (Timer1_CLK) | (TCCR1B & 0XF8);
}

void Timer1_Stop(void)
{
	TCCR1B &= 0XF8;
}

/*------------------------------------>Timer2<-----------------------------------------------*/
void Timer2_Init(void)
{
	// Global Interrupt
	SREG |= Global_INT << 7;
	
	// Timer2_Modes
	#if Timer2_Mode == Timer2_OVF
		Clear_Bit(TCCR2, 3);
		Clear_Bit(TCCR2, 6);
	
	// Timer2_Perpheral Interrupt Enable/Disable
		TIMSK = (Timer2_OVF_INT << 6) | (TIMSK & 0XBF);
	
	#elif Timer2_Mode == Timer2_P_PWM
		Clear_Bit(TCCR2, 3);
		Set_Bit(TCCR2, 6);
	
	
	#elif Timer2_Mode == Timer2_CTC
		Set_Bit(TCCR2, 3);
		Clear_Bit(TCCR2, 6);
	
	// Timer2_Perpheral Interrupt Enable/Disable
		TIMSK = (Timer2_CTC_INT << 7) | (TIMSK & 0X7F);
	
	#elif Timer2_Mode == Timer2_F_PWM
		Set_Bit(TCCR2, 3);
		Set_Bit(TCCR2, 6);
	
	#endif
}

void Timer2_SetDelay(Uint32 delay_ms)
{
	Uint8 Tick_Time_us = 0;
	Uint32 Tick_num = 0;
	Tick_Time_us = Timer2_Freq_Divider / MC_Freq_MHz;
	Tick_num = (delay_ms*1000) / Tick_Time_us;
	
	#if Timer2_Mode == Timer2_OVF
		if(Tick_num <= 256)
		{
			Timer2_Init_Value = 256 - Tick_num;
			TCNT2 = Timer2_Init_Value;
			Timer2_Num_OVF = 1;
		}
		else
		{
			Timer2_Num_OVF = !(Tick_num % 256) ? (Tick_num / 256) : (Tick_num / 256) + 1;
			Timer2_Init_Value = 256 - (Tick_num % 256);
			TCNT2 = Timer2_Init_Value;
		}
	#elif Timer2_Mode == Timer2_CTC
		if(Tick_num <= 256)
		{
			Timer2_Init_Value = Tick_num - 1;
			OCR2 = Timer2_Init_Value;
			Timer2_Num_OVF = 1;
		}
		else
		{
			Timer2_Num_OVF = !(Tick_num % 256) ? (Tick_num / 256) : (Tick_num / 256) + 1;
			Timer2_Init_Value = (Tick_num % 256) - 1;
			OCR2 = Timer2_Init_Value;
		}
	
	#endif
}

void Timer2_Start(void)
{
	TCCR2 = (Timer2_CLK) | (TCCR2 & 0XF8);
}
void Timer2_Stop(void)
{
	TCCR2 &= 0XF8;
}

void PWM2_Gen(f32 Duty_Cycle)
{
	if(Duty_Cycle < 0)
		Duty_Cycle = 0;
	else if(Duty_Cycle > 100)
		Duty_Cycle = 100;
	
	#if Timer2_Mode == Timer2_F_PWM
		#if F_PWM2_Mode == F_OC2_C_Comp_S_TOP
			OCR2 = !Duty_Cycle? 0 : ((Duty_Cycle / 100) * 256) - 1;
	
		#elif F_PWM2_Mode == F_OC2_S_Comp_C_TOP
			OCR2 = Duty_Cycle == 100? 0 : 255 - ((Duty_Cycle / 100) * 256);
	
		#endif
	#elif Timer2_Mode == Timer2_P_PWM
		#if P_PWM2_Mode == P_OC2_C_CompU_S_CompD
			OCR2 = Duty_Cycle * 255 / 100;
	
		#elif P_PWM2_Mode == P_OC2_S_CompU_C_CompD
			OCR2 = 255 - (Duty_Cycle * 255 / 100);
	
		#endif
	#endif
}

ISR(TIMER2_OVF_vect)
{
	static Uint32 Count = 0;
	Count++;
	if(Timer2_Num_OVF == Count)
	{
		// Write OVF of Timer_2 handler here
		
		
		Count = 0;
		TCNT2 = Timer2_Init_Value;
	}
	
}

ISR(TIMER2_COMP_vect)
{
	static Uint32 Count = 0;
	Count++;
	if(Count == 1 && Timer2_Num_OVF == Count)
	{
		// Write CMP of Timer_2 handler here
		
				
		Count = 0;
		OCR2 = Timer2_Init_Value;
	}
	else if(Count == 1)
	OCR2 = 255;
	else if(Timer2_Num_OVF == Count)
	{
		// Write CMP of Timer_2 handler here
		
		
		Count = 0;
		OCR2 = Timer2_Init_Value;
	}
}
