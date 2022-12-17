/*
 * DC_Motor.h
 *
 * Created: 7/27/2021 7:51:50 PM
 *  Author: ahmed
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "DC_Motor_CFG.h"

typedef enum
{
	Clock_Wise,
	Anti_Clock_Wise
		}DC_Motor_Dir;

/*DC_Motor1 Functions prototype*/
void DC_Motor1_INIT(void);

void DC_Motor1_START(Uint16 duty_cycle, DC_Motor_Dir dir);

void DC_Motor1_STOP(void);

/*DC_Motor2 Functions prototype*/
void DC_Motor2_INIT(void);

void DC_Motor2_START(Uint16 duty_cycle, DC_Motor_Dir dir);

void DC_Motor2_STOP(void);


#endif /* DC_MOTOR_H_ */