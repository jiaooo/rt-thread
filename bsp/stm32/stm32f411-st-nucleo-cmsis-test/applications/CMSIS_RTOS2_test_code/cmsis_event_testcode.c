#include <stdio.h>
#include <cmsis_os2.h>

static osThreadId_t thread1;
static osThreadId_t thread2;
static osThreadId_t thread3;
static osThreadId_t thread4;

osEventFlagsId_t evt_id;

void thread1_funct(void* argument)
{
    int16_t count = 0;
    uint32_t flag1;
    
    while(1)
    {
        count++;
        printf("thread1 run: %d \n",count);
        
         if((count % 6) == 0)
        {
            printf("thread1 will set flag!\n");
            flag1 = osEventFlagsSet(evt_id, 0x01);
            printf("after thread1 set,event flag value is:%d \n",flag1);
        }
        else if((count % 7) == 0)
        {
            printf("thread1 will set flag!\n");
            flag1 = osEventFlagsSet(evt_id, 0x02);
            printf("after thread1 set,event flag value is:%d \n",flag1);
        }
        else if((count % 8) == 0)
        {
            printf("thread1 will set flag!\n");
            flag1 = osEventFlagsSet(evt_id, 0x04);
            printf("after thread1 set,event flag value is:%d \n",flag1);
        }
        else if((count % 9) == 0)
        {
            printf("thread1 will set flag!\n");
            flag1 = osEventFlagsSet(evt_id, 0x08);
            printf("after thread1 set,event flag value is:%d \n",flag1);
        }
        else if((count % 10) == 0)
        {
            printf("thread1 will set flag!\n");
            flag1 = osEventFlagsSet(evt_id, 0x10);
            printf("after thread1 set,event flag value is:%d \n",flag1);
        }
        else if((count % 11) == 0)
        {
            printf("thread1 will set flag!\n");
            flag1 = osEventFlagsSet(evt_id, 0x20);
            printf("after thread1 set,event flag value is:%d \n",flag1);
        }
        
        osDelay(3000);
    }
}

void thread2_funct(void* argument)
{
    int16_t count = 0;
    uint32_t flag2;
    
    while(1)
    {
        count++;
        printf("thread2 run: %d \n",count);

        if ((count % 3) == 0)
        {
            printf("thread2 will wait all flag!\n");    /* wait 0b0000,0111 */
            flag2 = osEventFlagsWait(evt_id,0x07, osFlagsWaitAll, osWaitForever);
            printf("after thread2 waited,event flag value is:%d \n",flag2);
        }

        osDelay(3000);
    }
}

void thread3_funct(void* argument)
{
    int16_t count = 0;
    uint32_t flag3;
    
    while(1)
    {
        count++;
        printf("thread3 run: %d \n",count);
        
        if ((count % 4) == 0)
        {
            printf("thread3 will wait any flag!\n");    /* wait 0b0000,1100 */
            flag3 = osEventFlagsWait(evt_id,0x0c, osFlagsWaitAny, osWaitForever);
            printf("after thread3 waited,event flag value is:%d \n",flag3);
        }
        
        osDelay(3000);
    }
}

void thread4_funct(void* argument)
{
    int16_t count = 0;
    uint32_t flag4;
    
    while(1)
    {
        count++;
        printf("thread4 run: %d \n",count);
        
        if ((count % 5) == 0)
        {
            printf("thread4 will wait all flag!\n");    /* wait 0b0011,0000 */
            flag4 = osEventFlagsWait(evt_id,0x30, osFlagsWaitAll | osFlagsNoClear, osWaitForever);
            printf("after thread4 waited,event flag value is:%d \n",flag4);
            osEventFlagsClear(evt_id,0x30);
            flag4 = osEventFlagsGet(evt_id);
            printf("thread4 geted event flag value is:%d\n",flag4);
            printf("event flag name is:%s\n",osEventFlagsGetName(evt_id));
        }
        
        osDelay(3000);
    }
}

void threadflag_main(void)
{
    osThreadAttr_t thread1_attr = {.priority = osPriorityHigh};
    osThreadAttr_t thread2_attr = {.priority = osPriorityHigh4};
    osThreadAttr_t thread3_attr = {.priority = osPriorityHigh5};
    osThreadAttr_t thread4_attr = {.priority = osPriorityHigh6};
    
    evt_id = osEventFlagsNew(NULL);
    
    thread1 = osThreadNew(thread1_funct, NULL, &thread1_attr);
    if(NULL != thread1)
    {
        printf("thread1 created successfully!\n");
    }

    thread2 = osThreadNew(thread2_funct, NULL, &thread2_attr);
    if(NULL != thread2)
    {
        printf("thread2 created successfully!\n");
    }

    thread3 = osThreadNew(thread3_funct, NULL, &thread3_attr);
    if(NULL != thread3)
    {
        printf("thread3 created successfully!\n");
    }
    
    thread4 = osThreadNew(thread4_funct, NULL, &thread4_attr);
    if(NULL != thread4)
    {
        printf("thread4 created successfully!\n");
    }
}



