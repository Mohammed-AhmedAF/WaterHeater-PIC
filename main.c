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

Task_Type taskCount;

void main(void) {
    
    APP_vidInit();
    

    ADCON1 |= 0b11110110;
    
    /*Task initialization*/
    taskCount.ptrfun = vidCount;
    taskCount.u16FirstDelay = 100;
    taskCount.u16Periodicity = 100;
    taskCount.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    
    SCHEDULER_vidInit(SCHEDULER_GLOBALINTERRUPT_RAISED);

    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskCount),SCHEDULER_TASK0);
    
    
    while(1)
    {

    }
}