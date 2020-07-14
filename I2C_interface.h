/* 
 * File:   I2C_interface.h
 * Author: Mohammed
 *
 * Created on February 24, 2020, 10:16 AM
 */

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H

void I2C_vidInit(u8);
void I2C_vidSendStart(void);
void I2C_vidSendRepeatedStart(void);
u8 I2C_vidSendByte(u8);
void I2C_vidSendStop(void);
u8 I2C_u8ReceiveByte(void);
void I2C_vidSendNACK(void);
u8 I2C_u8ReceiveWithNoACK(void);
u8 I2C_u8CheckACK(void);
void I2C_vidWait(void);
void I2C_vidSendRepeatedStart(void);
#define I2C_MODE_MASTER 0

#endif	/* I2C_INTERFACE_H */

