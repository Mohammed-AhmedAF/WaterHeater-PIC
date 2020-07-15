#include "xc.h"
#include "Std_Types.h"
#include "Macros.h"
#include "COMMON_private.h"
#include "ADC_private.h"
#include "ADC_interface.h"

void ADC_vidInit(void)
{
    /*Channel selection*/
    CLEAR_BIT(ADCON0,3);
    CLEAR_BIT(ADCON0,4);
    CLEAR_BIT(ADCON0,5);
    
}

void ADC_vidStartConversion(void)
{
    SET_BIT(ADCON0,0);
}

u8 ADC_u8GetReading(void)
{
    /*Wait for conversion to complete*/
    while ((ADCON0,2) == 1);
    
    return ADRESL;
    
}