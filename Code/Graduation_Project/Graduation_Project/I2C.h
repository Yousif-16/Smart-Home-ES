/*
 * I2C.h
 *
 * Created: 7/31/2021 6:31:38 PM
 *  Author: ahmed
 */ 
#ifndef I2C_H_
#define I2C_H_

#include "I2C_CFG.h"

/*TWCR Register Bits*/
#define TWIE          0
#define TWEN          2
#define TWWC          3
#define TWSTO         4
#define TWSTA         5
#define TWEA          6
#define TWINT         7

/*Master general status codes*/
#define TRANS_START_COND               0X08  //A START condition has been transmitted
#define TRANS_REP_START_COND           0X10  //A repeated START condition has been transmitted
#define ARBITRATION_LOST               0X38  //Arbitration lost in SLA+W or data bytes

/*Master Transmitter status codes*/
#define TRANS_SLA_W_REC_ACK            0X18  //SLA+W has been transmitted, ACK has been received
#define TRANS_SLA_W_REC_NACK           0X20  //SLA+W has been transmitted, NOT ACK has been received
#define M_TRANS_DATA_REC_ACK           0X28  //Data has been transmitted, ACK has been received
#define M_TRANS_DATA_REC_NACK          0X30  //Data has been transmitted, NOT ACK has been received

/*Master Receiver status codes*/
#define TRANS_SLA_R_REC_ACK            0X40  //SLA+R has been transmitted, ACK has been received
#define TRANS_SLA_R_REC_NACK           0X48  //SLA+R has been transmitted, NOT ACK has been received
#define M_REC_DATA_TRANS_ACK           0X50  //Data has been received, ACK has been returned
#define M_REC_DATA_TRANS_NACK          0X58  //Data has been received, NOT ACK has been returned

/*Slave Receiver status codes*/
#define REC_SLA_W_TRANS_ACK            0X60  //Own SLA+W has been received, ACK has been returned
#define ARB_LOST_REC_SLA_W_TRANS_ACK   0X68  //Arbitration lost in SLA+R/W as master, own SLA+W has been received, ACK has been returned
#define REC_GCA_TRANS_ACK              0X70  //General call address has been received, ACK has been returned
#define ARB_LOST_REC_GCA_TRANS_ACK     0X78  //Arbitration lost in SLA+R/W as master, General call address has been received, ACK has been returned
#define S_REC_DATA_TRANS_ACK           0X80  //Previously addressed with own SLA+W, data has been received, ACK has been returned
#define S_REC_DATA_TRANS_NACK          0X88  //Previously addressed with own SLA+W, data has been received, NOT ACK has been returned
#define S_GCA_REC_DATA_TRANS_ACK       0X90  //Previously addressed with general call, data has been received, ACK has been returned
#define S_GCA_REC_DATA_TRANS_NACK      0X98  //Previously addressed with general call, data has been received, NOT ACK has been returned
#define REC_STOP_REP_START_CONDs       0XA0  //A STOP condition or repeated START condition has been received while still addressed as slave

/*Slave Transmitter status codes*/
#define REC_SLA_R_TRANS_ACK            0XA8  //Own SLA+R has been received, ACK has been returned
#define ARB_LOST_REC_SLA_R_TRANS_ACK   0XB0  //Arbitration lost in SLA+R/W as master, own SLA+R has been received, ACK has been returned
#define S_TRANS_DATA_REC_ACK           0XB8  //Data byte in TWDR has been transmitted, ACK has been received
#define S_TRANS_DATA_REC_NACK          0XC0  //Data byte in TWDR has been transmitted, NOT ACK has been received
#define S_TRANS_LAST_DATA_REC_ACK      0XC8  //Last data byte in TWDR has been transmitted (TWEA = “0”), ACK has been received

/*Call back functions prototype*/
void I2C_callback0(void(*p)());
void I2C_callback1(void(*p)(Uint8 *));

void I2C_INIT(void);

void I2C_SendStartCond(void);
void I2C_SendRepStartCond(void);

void I2C_SendSlaveAdd_WriteOP(Uint8 SLA_Add);
void I2C_SendSlaveAdd_ReadOP(Uint8 SLA_Add);

void I2C_SendData(Uint8 Data);
void I2C_SendMultiData(Uint8* Data, Uint8 Data_Size);
void I2C_SendString(Uint8* Data);

Uint8 I2C_ReadData(void);
Uint8 I2C_ReadMultiData(void);

void I2C_SendStopCond(void);

#endif /* I2C_H_ */