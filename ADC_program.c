#include "xc.h"
#include "Std_Types.h"
#include "Macros.h"
#include "COMMON_private.h"
#include "ADC_private.h"
#include "ADC_interface.h"

#define _XTAL_FREQ 4000000 
void ADC_vidInit(void)
{
        ADCON0 = 0b11001011;

       /* A/D Conversion Clock FOSC/2*/
    ADCS1 = 0;
    ADCS0 = 0;
    
 


}

u16 ADC_u8GetReading(u8 u8ChannelNumber)
{
 
/*A/D converter module is powered up*/
    ADON = 1;
    
    /*Clear previous channel*/
    ADCON0 &= 0b11001011;
    
    /*Set new channel*/
    ADCON0 |= u8ChannelNumber<<3;
    __delay_ms(1);
    
    /*Start ADC conversion*/
    GO = 1;
    
    /*wait until done*/
    while (GO_DONE == 1);
    
    /*A/D converter module is shut-off*/
    ADON = 0;
    
    /*return result*/
    return((ADRESH<<8) + ADRESL);
}