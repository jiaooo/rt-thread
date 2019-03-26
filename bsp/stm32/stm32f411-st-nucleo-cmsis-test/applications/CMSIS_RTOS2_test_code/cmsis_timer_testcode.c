#include <stdio.h>
#include <cmsis_os2.h>

static osThreadId_t thread1;
osTimerId_t one_shot_id, periodic_id;

void thread1_funct(void* argument)
{
    int16_t count = 0;
    while(1)
    {
        count++;
        printf("thread1 run %d \n",count);
        
         if(5 == count)
        {
            if(osTimerStop(periodic_id) == osOK)
            {
                printf("periodic timer is stoped\n");
            }           
            if(osTimerIsRunning(periodic_id) != 1)
            {
                printf("periodic timer is not running\n");
            }
        }
        else if(15 == count)
        {
            if(osTimerStart(periodic_id,4000) == osOK)
            {
                printf("periodic timer start again\n");
            }
        }
        else if(20 == count)
        {
            if(osTimerDelete(periodic_id) == osOK)
            {
                printf("periodic timer is deleted\n");
            }
        }
        
        osDelay(5000);
    }
}

static void one_shot_Callback (void *argument)
{
    int32_t arg = (int32_t)argument; // cast back argument '0' 
                                    // do something, i.e. set thread/event flags
    printf("one-shot timer callback,argument = %d\n",arg);
}
static void periodic_Callback (void *argument)
{
    int32_t arg = (int32_t)argument; // cast back argument '5'
                                    // do something, i.e. set thread/event flags
    printf("periodic timer callback,argument = %d\n",arg);
}



void timer_main(void)
{
    thread1 = osThreadNew(thread1_funct, NULL, NULL);
    if(NULL != thread1)
    {
        printf("thread1 created successfully!\n");
    }

    // creates a one-shot timer:
    one_shot_id = osTimerNew(one_shot_Callback, osTimerOnce, (void *)1, NULL);
    if(one_shot_id)
    {
        if (osTimerStart(one_shot_id, 5000) == osOK)
        {
            printf("one-shot timer start!\n");
        }
    }
    // creates a periodic timer:
    periodic_id = osTimerNew(periodic_Callback, osTimerPeriodic, (void *)2, NULL);
    if(periodic_id)
    {
        if (osTimerStart(periodic_id, 3000) == osOK)
        {
            printf("periodic timer start!\n");
        }
    }
    
     printf("get timer name is :%s\n",osTimerGetName(one_shot_id));
     printf("get timer name is :%s\n",osTimerGetName(periodic_id));

}

