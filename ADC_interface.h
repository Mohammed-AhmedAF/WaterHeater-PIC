/* 
 * File:   ADC_interface.h
 * Author: Mohammed
 *
 * Created on July 15, 2020, 2:31 AM
 */

#ifndef ADC_INTERFACE_H
#define	ADC_INTERFACE_H

void ADC_vidInit();
u16 ADC_u8GetReading(u8 u8ChannelNumber);

#define ADC_CHANNEL0 0
#define ADC_CHANNEL1 1
#define ADC_CHANNEL2 2
#define ADC_CHANNEL3 3
#define ADC_CHANNEL4 4


#endif	/* ADC_INTERFACE_H */

