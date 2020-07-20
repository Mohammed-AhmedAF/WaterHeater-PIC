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
#include "COMMON_private.h"
#include "INTERRUPTS_interface.h"


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
    
    DIO_vidSetPinDirection(DIO_PORTB,DIO_PIN0,DIO_INPUT);
        DIO_vidControlPullUp(DIO_PULLUP);

        
    /*RB0 interrupt*/
    INTERRUPTS_vidEnableInterrupt(INTERRUPTS_EXT_INT0);
    INTERRUPTS_vidSetExtInterruptEdge(INTERRUPTS_EDGE_FALLING);
    INTERRUPTS_vidPutISR(INTERRUPTS_EXT_INT0,APP_vidGetButtons);
    
    /*RB4, RB5 interrupt*/
    INTERRUPTS_vidEnableInterrupt(INTERRUPTS_PORTB_CHANGE);
    INTERRUPTS_vidPutISR(INTERRUPTS_PORTB_CHANGE,APP_vidCheckIncDec);

    /*Heater*/
    DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN5,DIO_OUTPUT);
    
    /*Fan*/
    DIO_vidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
    
    /*ADC*/
    ADC_vidInit();

    /*Testing I2C*/
    I2C_vidInit(I2C_MODE_MASTER);
    __delay_ms(30);
    SEVENSEG_vidWriteNumber(u16Temperature);

    DIO_vidSetPinDirection(HLED_PORT,HLED_PIN,DIO_OUTPUT);
}

void vidCount(void) {
 
    u16ADCRes = ADC_u8GetReading(2);
    u16Temperature = (u16ADCRes * 0.488);

}

void APP_vidUpdateSevenSeg(void)
{
        SEVENSEG_vidWriteNumber(u8Number);
        APP_vidAdjustTemperature();

}

void APP_vidGetButtons(void)
{
        u8Number++;
        DIO_vidTogglePin(DIO_PORTB,DIO_PIN7);
        DIO_vidSetPinValue(DIO_PORTC,DIO_PIN5,STD_HIGH);


}

void APP_vidCheckIncDec(void)
{
    if (DIO_u8GetPinValue(DIO_PORTB,DIO_PIN4) == 0)
    {
        u8Number += 5;
    }
    if (DIO_u8GetPinValue(DIO_PORTB,DIO_PIN5) == 0)
    {
        if (u8Number >= 5)
        {
            u8Number -= 5;
        }
        else
        {
            u8Number = 5;
        }
            
    }
}

void APP_vidAdjustTemperature(void)
{
    u8 u8SetValue = 40;
    if (u16Temperature >= u8SetValue)
    {
        DIO_vidSetPinValue(HEATER_PORT,HEATER_PIN,STD_LOW);
        DIO_vidSetPinValue(HLED_PORT,HLED_PIN,STD_LOW);
    }
    if (u16Temperature < 30)
    {
        DIO_vidSetPinValue(HEATER_PORT,HEATER_PIN,STD_HIGH);
        DIO_vidSetPinValue(HLED_PORT,HLED_PIN,STD_HIGH);
    }
}