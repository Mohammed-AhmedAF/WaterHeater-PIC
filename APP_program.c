#include "xc.h"
#include "Macros.h"
#include "Std_Types.h"
#include "DIO_interface.h"
#include "I2C_interface.h"
#include "LCD_interface.h"
#include "SEVENSEG_interface.h"
#include "EEPROM_interface.h"
#include "ADC_interface.h"
#include "APP_interface.h"
#include "LCD_interface.h"


#define _XTAL_FREQ 40000000


volatile u8 u8Number = 0;

u8 u8Val = 0;
u8 u8Result = 0;
u16 u16ADCRes;
u16 u16Temperature;
u8 u8Flag = 1;

void APP_vidInit(void) {
    SEVENSEG_vidInit();
    DIO_vidSetPinDirection(DIO_PORTA, DIO_PIN2, DIO_INPUT);

    /*ADC*/
    ADC_vidInit();
    /*LCD*/

    /*Testing I2C*/
    I2C_vidInit(I2C_MODE_MASTER);
    __delay_ms(30);
    SEVENSEG_vidWriteNumber(u16Temperature);


}

void vidCount(void) {
    u8Result = EEPROM_u8ReadByte(0);
    u8Number++;
    if (u8Number > 99) {
        u8Number = 0;
    }
    u16ADCRes = ADC_u8GetReading(2);
    u16Temperature = (u16ADCRes * 0.488);

    
        SEVENSEG_vidWriteNumber(30);

  





}
