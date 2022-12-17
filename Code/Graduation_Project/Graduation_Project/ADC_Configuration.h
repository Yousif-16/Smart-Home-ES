/*
 * ADC_Configuration.h
 *
 * Created: 9/22/2022 11:51:18 AM
 *  Author: Dell
 */ 



#ifndef ADC_CONFIGURATION_H_
#define ADC_CONFIGURATION_H_
#include "DIO.h"
#include "Interrupt.h"

// ADC Voltage Reference chosen
#define ADC_Volt_Ref ADC_AVCC

// ADC Pre_scaler
#define  ADC_CLK ADC_CLK_128

// ADC Right/Left Adjust
#define ADC_Data_Presentation ADC_Right_Adjust

// ADC Mode
#define ADC_Cov_Mode Auto_Triggered_Mode

// Type of Auto Triggered Mode
#define  ADC_Auto_Triggered_Mode_Type Free_Running

#endif /* ADC_CONFIGURATION_H_ */