#include <xc.h>
#include "config.h"
#include "Std_Types.h"
#include "COMMON_private.h"
#include "DIO_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER0_interface.h"
#include "SCHEDULER_interface.h"
#include "EEPROM_interface.h"
#include "APP_interface.h"

Task_Type taskUpdateDisp;
Task_Type taskGetTemperature;
Task_Type taskContMode;

void main(void) {
    
    APP_vidInit();
    
    /*Task initialization*/
    taskUpdateDisp.ptrfun = APP_vidUpdateSevenSeg;
    taskUpdateDisp.u16FirstDelay = 0;
    taskUpdateDisp.u16Periodicity = 1;
    taskUpdateDisp.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    taskGetTemperature.ptrfun = APP_vidGetTemperature;
    taskGetTemperature.u16FirstDelay = 0;
    taskGetTemperature.u16Periodicity = 156;
    taskGetTemperature.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    
    taskContMode.ptrfun = APP_vidContMode;
    taskContMode.u16FirstDelay = 0;
    taskContMode.u16Periodicity = 250;
    taskContMode.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
  
    SCHEDULER_vidInit(SCHEDULER_GLOBALINTERRUPT_RAISED);

    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskUpdateDisp),SCHEDULER_TASK0);
    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskGetTemperature),SCHEDULER_TASK1);
    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskContMode),SCHEDULER_TASK2);
    
    while(1)
    {
  
    }
}