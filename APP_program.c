#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include "I2C_interface.h"
#include "SEVENSEG_interface.h"
#include "EEPROM_interface.h"
#include "APP_interface.h"

volatile u8 u8Number = 0;

u8 u8Val = 0;
u8 u8Result = 0;

void APP_vidInit(void)
{
    SEVENSEG_vidInit();
    
    DIO_vidSetPortValue(DIO_PORTA,0x00);
 
    /*Testing I2C*/
    I2C_vidInit(I2C_MODE_MASTER);
}

void vidCount(void)
{
        
       
        u8 u8Val = 'b';
        EEPROM_vidWriteByte(0,u8Val);
        u8Number++;
        if (u8Number > 99)
        {
            u8Number = 0;
        }
        SEVENSEG_vidWriteNumber(u8Result);
      
     
        
}
