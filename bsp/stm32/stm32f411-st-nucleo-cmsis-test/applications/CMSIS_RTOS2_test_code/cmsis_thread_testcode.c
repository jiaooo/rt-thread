#include <stdio.h>
#include <cmsis_os2.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

static osThreadId_t thread1;
//static osThreadId_t thread2;
//static osThreadId_t thread3;
//static osThreadId_t thread4;
//static osThreadId_t thread5;

void thread1_funct(void* argument)
{
    int16_t count = 0;
    while(1)
    {
        count++;
        rt_kprintf("thread1 run: %d \n",count);
        osDelay(3000);
    }
}


int thread_main(int argc, char**argv)
{

    osThreadAttr_t thread_attr = {.priority = osPriorityHigh,.attr_bits = osThreadJoinable};

    osKernelInitialize();

    thread1 = osThreadNew(thread1_funct, NULL, NULL);
    if(NULL != thread1)
    {
        rt_kprintf("thread1 created successfully!\n");
    }

    osKernelStart();
    
    return 0;
}

MSH_CMD_EXPORT(thread_main, thread_main sample);

