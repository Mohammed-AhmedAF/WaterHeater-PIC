#include "xc.h"
#include "Std_Types.h"
#include "Macros.h"
#include "COMMON_private.h"
#include "ADC_private.h"
#include "ADC_interface.h"

#define _XTAL_FREQ 4000000 
void ADC_vidInit(void)
{

       /* A/D Conversion Clock FOSC/2*/
    CLEAR_BIT(ADCON0,6);
    CLEAR_BIT(ADCON0,7);
    CLEAR_BIT(ADCON1,6);
 
    SET_BIT(ADCON1,7);

}

u16 ADC_u8GetReading(u8 u8ChannelNumber)
{
 
/*A/D converter module is powered up*/
    ADON = 1;
    
    /*Clear previous channel*/
    ADCON1 &= 0b11000111;
    
    /*Set new channel*/
    //ADCON0 |= 2<<3;
    ADCON0 |= u8ChannelNumber << 3;
    __delay_ms(12);
    
    /*Start ADC conversion*/
    GO = 1;
    
    /*wait until done*/
    while (GO_DONE == 1);
    
    /*A/D converter module is shut-off*/
    ADON = 0;
    
    /*return result*/
    return((ADRESH<<8) + ADRESL);
}