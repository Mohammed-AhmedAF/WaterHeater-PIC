#include <xc.h>
#include "config.h"
#include "Std_Types.h"
#include "COMMON_private.h"
#include "DIO_interface.h"
#include "INTERRUPTS_interface.h"
#include "TIMER0_interface.h"
#include "SCHEDULER_interface.h"
#include "SEVENSEG_interface.h"


void vidCount(void);

volatile u8 u8Number = 0;

Task_Type taskCount;

void main(void) {
    
    SEVENSEG_vidInit();
    
    DIO_vidSetPortValue(DIO_PORTA,0x00);
    

    ADCON1 |= 0b11110110;
    
    /*Task initialization*/
    taskCount.ptrfun = vidCount;
    taskCount.u16FirstDelay = 0;
    taskCount.u16Periodicity = 1500;
    taskCount.u8State = SCHEDULER_TASKSTATE_RUNNING;
    
    SCHEDULER_vidInit(SCHEDULER_GLOBALINTERRUPT_RAISED);

    SCHEDULER_vidCreateTask(_SCHEDULER_GETID(taskCount),SCHEDULER_TASK0);
    
    
    while(1)
    {

    }
}

void vidCount(void)
{

        u8Number++;
        if (u8Number > 99)
        {
            u8Number = 0;
        }
        SEVENSEG_vidWriteNumber(u8Number);
  
}