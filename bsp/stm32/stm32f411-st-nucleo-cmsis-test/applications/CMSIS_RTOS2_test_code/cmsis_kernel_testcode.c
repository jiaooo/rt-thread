#include <stdio.h>
#include <cmsis_os2.h>

static osThreadId_t thread1;
static osThreadId_t thread2;

void thread1_funct(void* argument)
{
    int16_t count = 0;
    while(1)
    {
        count++;
        printf("thread1 run: %d \n",count);
  
        osDelay(5000);
    }
}

void thread2_funct(void* argument)
{
    int16_t count = 0;

    while(1)
    {
        count++;
        printf("thread2 run %d \n",count);
        
         if(5 == count)
        {
            uint32_t tick;
            tick = osKernelGetTickCount();
            printf("the current tick frequence is:%d\n",osKernelGetTickFreq());
            printf("the current tick is:%d,thread1 will delay until:%d\n",tick,tick+4000);
            osDelayUntil(tick+4000);
            printf("thread2 has delayed 4000 ticks\n");
        }
        else if(10 == count)
        {
            char infobuf[16];
            osVersion_t osv;
            osStatus_t status;

            status = osKernelGetInfo(&osv, infobuf, sizeof(infobuf));
            if(status == osOK)
            {
                printf("Kernel Information: %s\n", infobuf);
                printf("Kernel Version    : %d\n", osv.kernel);
                printf("Kernel API Version: %d\n", osv.api);
            }
            printf("Kernel state: %d\r\n", osKernelGetState());
        }
        else if(15 == count)
        {
            uint32_t sl = osKernelLock();
            {
                uint32_t su;
                printf("Kernel locked,state: %d\n", osKernelGetState());
                 su = osKernelUnlock();
                printf("Kernel unlocked,state: %d\n", osKernelGetState());
                osKernelRestoreLock(su);
                printf("Kernel restorelock,state: %d\n", osKernelGetState());
            }
            osKernelRestoreLock(sl);
            printf("Kernel restorelock,state: %d\n", osKernelGetState());
        }
        
        osDelay(5000);
    }
}

void kernel_main(void)
{
    thread1 = osThreadNew(thread1_funct, NULL, NULL);
    if(NULL != thread1)
    {
        printf("thread1 created successfully!\n");
    }

    thread2 = osThreadNew(thread2_funct, NULL, NULL);
    if(NULL != thread2)
    {
        printf("thread2 created successfully!\n");
    }

}


