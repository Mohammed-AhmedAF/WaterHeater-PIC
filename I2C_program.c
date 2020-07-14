#include "Macros.h"
#include "Std_Types.h"
#include "COMMON_private.h"
#include "DIO_interface.h"
#include "I2C_private.h"
#include "I2C_interface.h"

void I2C_vidInit(u8 u8Mode)
{
    if (u8Mode == I2C_MODE_MASTER)
    {
        /*Selecting master mode*/
        /*SSPM3:SSPM0 1000*/
        CLEAR_BIT(SSPCON1,0);
        CLEAR_BIT(SSPCON1,1);
        CLEAR_BIT(SSPCON1,2);
        SET_BIT(SSPCON1,3);
        
        /*Synchronous serial port enable*/
        SET_BIT(SSPCON1,5);
        
        SSPCON2 = 0;
        
        /*SCL pin set as input*/
        DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_INPUT);
        
        /*SDA pin set as input*/
        DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_INPUT);
        /*Set speed*/
        SSPADD = 9;
        SSPSTAT = 0;       
       
    }
    /*Slave mode*/
    else
    {
        
    }
}

void I2C_vidSendStart(void)
{        
    I2C_vidWait();
    /*Enable start condition*/
    SET_BIT(SSPCON2,0);
}

void I2C_vidSendStop(void)
{
    I2C_vidWait();
    /*Stop condition enabled*/
    SET_BIT(SSPCON2,2);
    
}

void I2C_vidSendRepeatedStart(void)
{
    I2C_vidWait();
    SET_BIT(SSPCON2,1);
}

u8 I2C_vidSendByte(u8 u8Byte)
{
    
    I2C_vidWait();
    SSPBUFF = u8Byte;
    while(GET_BIT(PIR1,7) == 0);
    CLEAR_BIT(PIR1,7);
    
    return I2C_u8CheckACK();
}

u8 I2C_u8ReceiveWithACK(void)
{       
    
    /*Bit4: Acknowledge enable*/
    /*Receive enabled*/
    SET_BIT(SSPCON2,3);
    while(GET_BIT(PIR1,7) == 0);
    CLEAR_BIT(PIR1,7);
    return SSPBUFF;
    
}

u8 I2C_u8ReceiveByte(void)
{
    
    I2C_vidWait();
    
    /*Bit4: Acknowledge enable*/
    /*Receive enabled*/
    SET_BIT(SSPCON2,3);
    
    while(GET_BIT(SSPSTAT,0) == 0);

    while(GET_BIT(PIR1,7) == 0);
    CLEAR_BIT(PIR1,7);
    
    I2C_vidWait();
    return SSPBUFF;
}

void I2C_vidSendNACK(void)
{
    
   /*SEND NACK*/
    SET_BIT(SSPCON2,5);
    I2C_vidWait();
    SET_BIT(SSPCON2,4);
}

void I2C_vidWait(void)
{
  while ((SSPCON2 & 0x1F));
}

u8 I2C_u8CheckACK(void)
{
    
    /*Return ACKSTAT bit, inverted because it is 1 on NACK, 0 on ACK*/
    u8 val = GET_BIT(SSPCON2,6);
    if (val == 1){
        return 0;
    }
    else
    {
        return 1;
    }
    
}