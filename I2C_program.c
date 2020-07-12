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
        
        SET_BIT(SSPCON1,5);
         DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_INPUT);
        DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_INPUT);
        /*Set speed*/
        SSPADD = 9;
        SSPSTAT = 0;       
       
    }
    else
    {
        
    }
}

void I2C_vidSendStart(void)
{        
    //DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);
    /*Enable start condition*/
    SET_BIT(SSPCON2,0);
}

void I2C_vidSendStop(void)
{
    //DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);
    /*Stop condition enabled*/
    SET_BIT(SSPCON2,2);
    
}

void I2C_vidSendRepeatedStart(void)
{
    SET_BIT(SSPCON2,1);
}

void I2C_vidSendByte(u8 u8Byte)
{
    
    while(GET_BIT(SSPSTAT,2) == 1);
    SSPBUFF = u8Byte;
}

u8 I2C_u8ReceiveWithACK(void)
{       
    //DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_INPUT);
    
    /*Bit4: Acknowledge enable*/
    /*Receive enabled*/
    SET_BIT(SSPCON2,3);
    while(GET_BIT(SSPSTAT,0) == 0);
    SET_BIT(SSPCON2,4);
    return SSPBUFF;
}

void I2C_vdiSendACK(void)
{
}

void I2C_vidHold(void)
{
    
}