/*
 * Interrupt_Configuration.h
 *
 * Created: 9/21/2022 12:31:45 PM
 *  Author: Dell
 */ 


#ifndef INTERRUPT_CONFIGURATION_H_
#define INTERRUPT_CONFIGURATION_H_

/*--------------->Global Interrupt<-------------------*/

#define Global_INT Enable

/*--------------->External Interrupt<-------------------*/

#define Ext0_INT Enable
#define Ext1_INT Disable
#define Ext2_INT Disable

/*---------------->ADC Interrupt<--------------------*/
#define  ADC_INT Enable

/*---------------->Timer0 Interrupt<--------------------*/
#define  Timer0_OVF_INT Enable
#define  Timer0_CTC_INT Enable

/*---------------->Timer1 Interrupt<--------------------*/
#define  Timer1_OVF_INT Disable
#define  Timer1_CTCA_INT Disable
#define  Timer1_CTCB_INT Disable
#define  Timer1_IN_CAPT_INT Disable

/*---------------->Timer2 Interrupt<--------------------*/
#define  Timer2_OVF_INT Enable
#define  Timer2_CTC_INT Enable

/*---------------->UART Interrupt<--------------------*/
#define UART_RX_INT Enable
#define UART_TX_INT Enable

/*---------------->I2C Interrupt<--------------------*/
#define I2C_INT Enable

#endif /* INTERRUPT_CONFIGURATION_H_ */