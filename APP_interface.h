/* 
 * File:   APP_interface.h
 * Author: Mohammed
 *
 * Created on July 13, 2020, 7:59 AM
 */

#ifndef APP_INTERFACE_H
#define	APP_INTERFACE_H

void APP_vidInit(void);
void vidCount(void);
void APP_vidGetButtons(void);
void APP_vidUpdateSevenSeg(void);
void APP_vidAdjustTemperature(void);
void APP_vidCheckIncDec(void);


#define HEATER_PORT DIO_PORTC
#define COOLER_PORT DIO_PORTC

#define HEATER_PIN DIO_PIN5
#define COOLER_PIN DIO_PIN2

#define HLED_PORT DIO_PORTB
#define HLED_PIN DIO_PIN7

#endif	/* APP_INTERFACE_H */

