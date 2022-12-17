/*
 * servoo.c
 *
 * Created: 18/10/2022 04:27:10 م
 *  Author: User
 */ 
#include "servoo.h"

void Servoo_Motor(Uint32 duty_Cycle){
	TCNT1=0;
	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
	OCR1A=duty_Cycle; /* set the compare value*/
	//Configure TIMER1
	/* Configure timer control register TCCR1A
     * 1. Clear OC1A on compare match (non inverting mode) COM1A1=1 COM1A0=0
     * 2. Disconnect OC1B  COM1B0=0 COM1B1=0
     * 3. FOC1A=0 FOC1B=0 because these bits are only active in case non-pwm mode
     * 4. Fast Pwm Mode with the TOP in ICR1 WGM10=0 WGM11=1 (Mode Number 14)
	 */
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
/* duty cycle of 97 to be 0 deg*/
/* duty cycle of 316 to be 90 deg*/

	
}
void Servo_INIT(void)
{
	DDRD|=(1<<PD4)|(1<<PD5);// servo pin
	Servoo_Motor(97);
}
void Servo_Open(void)
{
	Servoo_Motor(316);
}
void Servo_Close(void)
{
	Servoo_Motor(97);
}

