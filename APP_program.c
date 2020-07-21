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


volatile u8 u8Number = APP_INITIALTEMP;
/*Storing the state of whole system (on,off)*/
volatile u8 u8SystemState = APP_STATE_OFF;
volatile u8 u8SystemMode = APP_MODE_SETTING;
volatile u8 u8BtnPressed = 1;
volatile u16 u16ADCRes;
volatile u16 u16Temperature;
volatile u8 u8Timer = 0;

u8 u8Flag = 1;

void APP_vidInit(void) {
    SEVENSEG_vidInit();

    /*LM35 connected to pin A2*/
    DIO_vidSetPinDirection(DIO_PORTA, DIO_PIN2, DIO_INPUT);

    /*Pin B0, ON/OFF button*/
    DIO_vidSetPinDirection(DIO_PORTB, DIO_PIN0, DIO_INPUT);
    DIO_vidControlPullUp(DIO_PULLUP);

    /*Increase/Decrease buttons configured as input*/
    DIO_vidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_INPUT);
    DIO_vidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_INPUT);

    /*RB0 interrupt*/
    INTERRUPTS_vidEnableInterrupt(INTERRUPTS_EXT_INT0);
    INTERRUPTS_vidSetExtInterruptEdge(INTERRUPTS_EDGE_FALLING);
    INTERRUPTS_vidPutISR(INTERRUPTS_EXT_INT0, APP_vidCheckOnOff);

    /*RB4, RB5 interrupt*/
    INTERRUPTS_vidEnableInterrupt(INTERRUPTS_PORTB_CHANGE);
    INTERRUPTS_vidPutISR(INTERRUPTS_PORTB_CHANGE, APP_vidCheckIncDec);

    /*Heater*/
    DIO_vidSetPinDirection(DIO_PORTC, DIO_PIN5, DIO_OUTPUT);

    /*Fan*/
    DIO_vidSetPinDirection(DIO_PORTC, DIO_PIN2, DIO_OUTPUT);

    /*ADC*/
    ADC_vidInit();

    /*Testing I2C*/
    I2C_vidInit(I2C_MODE_MASTER);
    __delay_ms(30);

    DIO_vidSetPinDirection(HLED_PORT, HLED_PIN, DIO_OUTPUT);

    /*SevenSeg initially disabled*/
    SEVENSEG_vidDisableSevenSeg();

}

void APP_vidGetTemperature(void) {

    u16ADCRes = ADC_u8GetReading(2);
    u16Temperature = (u16ADCRes * 0.488);
    /*Only adjust temperature if the system is in operating mode*/
    if (u8SystemMode == APP_MODE_OPERATING)
    {
        APP_vidAdjustTemperature();
    }
}

void APP_vidUpdateSevenSeg(void) {
    if (u8SystemState == APP_STATE_ON) {
        if (u8SystemMode == APP_MODE_SETTING) {
            SEVENSEG_vidWriteNumber(u8Number);
        } else {
            SEVENSEG_vidWriteNumber(u16Temperature);
        }
    }

}

void APP_vidCheckOnOff(void) {
    if (u8SystemState == APP_STATE_OFF) {
        u8SystemState = APP_STATE_ON;
    } else {
        SEVENSEG_vidDisableSevenSeg();
        u8SystemState = APP_STATE_OFF;
        /*Cooler/Fan off*/
        DIO_vidSetPinValue(HEATER_PORT, HEATER_PIN, STD_LOW);
        DIO_vidSetPinValue(COOLER_PORT, COOLER_PIN, STD_LOW);
    }

}

void APP_vidCheckIncDec(void) {
    /*Only handle button clicks if system is on*/
    if (u8SystemState == APP_STATE_ON) {
        u8BtnPressed = 1;
        if (DIO_u8GetPinValue(DIO_PORTB, DIO_PIN4) == 0) {
            if (u8Number < 75) {
                u8Number += 5;
            }

        }
        if (DIO_u8GetPinValue(DIO_PORTB, DIO_PIN5) == 0) {
            if (u8Number >= 5) {
                u8Number -= 5;
            }

        }
    }
}

void APP_vidAdjustTemperature(void) {
        if (u16Temperature >= u8Number + 5) {
            DIO_vidSetPinValue(HEATER_PORT, HEATER_PIN, STD_LOW);
            /*Cooler on*/
            DIO_vidSetPinValue(COOLER_PORT, COOLER_PIN, STD_HIGH);
            DIO_vidSetPinValue(HLED_PORT, HLED_PIN, STD_LOW);
        }
        if (u16Temperature < u8Number - 5) {
            DIO_vidSetPinValue(HEATER_PORT, HEATER_PIN, STD_HIGH);

            /*Cooler off*/
            DIO_vidSetPinValue(COOLER_PORT, COOLER_PIN, STD_LOW);
            DIO_vidSetPinValue(HLED_PORT, HLED_PIN, STD_HIGH);
        }
}

void APP_vidContMode(void) {
    u8Timer++;
    if (u8Timer == 32)
    {
    if (u8BtnPressed == 1) {
        u8BtnPressed = 0;
        u8SystemMode = APP_MODE_SETTING;
    } else {
        u8SystemMode = APP_MODE_OPERATING;
    }
    u8Timer = 0;
    }
}