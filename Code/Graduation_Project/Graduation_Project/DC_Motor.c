/*
 * DC_Motor.c
 *
 * Created: 7/27/2021 7:51:25 PM
 *  Author: ahmed
 */ 

#include "DC_Motor.h"

/*DC_Motor1 Functions implementation*/
void DC_Motor1_INIT(void)
{
	/*DC motor pins direction*/
	DIO_SetPin_Dir(M1_PORT, M1_DIR_PIN1, PIN_OUT);
	DIO_SetPin_Dir(M1_PORT, M1_DIR_PIN2, PIN_OUT);
	
	/*DC motor pins value*/
	DIO_SetPin_Value(M1_PORT, M1_DIR_PIN1, PIN_OFF);
	DIO_SetPin_Value(M1_PORT, M1_DIR_PIN2, PIN_OFF);	
	
	/*generate clock for the timer*/
	Timer0_Start();
}

void DC_Motor1_START(Uint16 duty_cycle, DC_Motor_Dir dir)
{
	switch(dir)
	{
		case  Clock_Wise:
		DIO_SetPin_Value(M1_PORT, M1_DIR_PIN1, PIN_ON);
		DIO_SetPin_Value(M1_PORT, M1_DIR_PIN2, PIN_OFF);
		break;
		case Anti_Clock_Wise:
		DIO_SetPin_Value(M1_PORT, M1_DIR_PIN1, PIN_OFF);
		DIO_SetPin_Value(M1_PORT, M1_DIR_PIN2, PIN_ON);
		break;
		default:
		break;
	}	
	PWM0_Gen(duty_cycle);
}

void DC_Motor1_STOP(void)
{
	DIO_SetPin_Value(M1_PORT, M1_DIR_PIN1, PIN_OFF);
	DIO_SetPin_Value(M1_PORT, M1_DIR_PIN2, PIN_OFF);	
}

/*DC_Motor1 Functions implementation*/
void DC_Motor2_INIT(void)
{
	/*DC motor pins direction*/
	DIO_SetPin_Dir(M2_PORT, M2_DIR_PIN1, PIN_OUT);
	DIO_SetPin_Dir(M2_PORT, M2_DIR_PIN2, PIN_OUT);
	
	/*DC motor pins value*/
	DIO_SetPin_Value(M2_PORT, M2_DIR_PIN1, PIN_OFF);
	DIO_SetPin_Value(M2_PORT, M2_DIR_PIN2, PIN_OFF);	
	
	/*generate clock for the timer*/
	Timer0_Start();		
}

void DC_Motor2_START(Uint16 duty_cycle, DC_Motor_Dir dir)
{
	switch(dir)
	{
		case  Clock_Wise:
		DIO_SetPin_Value(M2_PORT, M2_DIR_PIN1, PIN_ON);
		DIO_SetPin_Value(M2_PORT, M2_DIR_PIN2, PIN_OFF);
		break;
		case Anti_Clock_Wise:
		DIO_SetPin_Value(M2_PORT, M2_DIR_PIN1, PIN_OFF);
		DIO_SetPin_Value(M2_PORT, M2_DIR_PIN2, PIN_ON);
		break;
		default:
		break;
	}
	PWM0_Gen(duty_cycle);
}

void DC_Motor2_STOP(void)
{
	DIO_SetPin_Value(M2_PORT, M2_DIR_PIN1, PIN_OFF);
	DIO_SetPin_Value(M2_PORT, M2_DIR_PIN2, PIN_OFF);
}
