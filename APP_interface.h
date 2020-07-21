/* 
 * File:   APP_interface.h
 * Author: Mohammed
 *
 * Created on July 13, 2020, 7:59 AM
 */

#ifndef APP_INTERFACE_H
#define	APP_INTERFACE_H

void APP_vidInit(void);
void APP_vidGetTemperature(void);
void APP_vidCheckOnOff(void);
void APP_vidUpdateSevenSeg(void);
void APP_vidAdjustTemperature(void);
void APP_vidCheckIncDec(void);
void APP_vidContMode(void);


#define HEATER_PORT DIO_PORTC
#define COOLER_PORT DIO_PORTC

#define HEATER_PIN DIO_PIN5
#define COOLER_PIN DIO_PIN2

#define HLED_PORT DIO_PORTB
#define HLED_PIN DIO_PIN7

#define APP_STATE_OFF 0
#define APP_STATE_ON 1

#define APP_MODE_SETTING 0
#define APP_MODE_OPERATING 1

#define APP_TIME_5SEC 781

#define APP_INITIALTEMP 60

#endif	/* APP_INTERFACE_H */

