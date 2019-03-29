#include <stdio.h>
#include <cmsis_os2.h>
#include <rtthread.h>

static osThreadId_t thread1;
static osThreadId_t thread2;
static osThreadId_t thread3;
static osThreadId_t thread4;
static osThreadId_t thread5;

void thread1_funct(void* argument)
{
    int16_t count = 0;
    while(1)
    {
        count++;
        printf("thread1 run: %d \n",count);

        if (1 == count)
        {
            printf("thread1 will join thread3!\n");
            osThreadJoin(thread3);
            printf("thread1 joined thread3!\n");
        }
        else if (5 == count)
        {
            printf("thread1 will join thread4!\n");
            osThreadJoin(thread4);
            printf("thread1 joined thread4!\n");
        }
        else if (10 == count)
        {
            uint32_t thread_count;
            osThreadId_t thread_array[20];
            printf("thread1 will detach thread5!\n");
            osThreadDetach(thread5);

            thread_count = osThreadEnumerate (thread_array, 20);
        }

        osDelay(3000);
    }
}

void thread2_funct(void* argument)
{
    int16_t count = 0;

    while(1)
    {
        count++;
        printf("thread2 run: %d \n",count);
        
         if(5 == count)
        {
            osThreadState_t threadstate;
            osStatus_t state;
            osThreadId_t thread_id = osThreadGetId();
            printf("thread2 name is:%s\n",osThreadGetName(thread_id));
            threadstate = osThreadGetState(thread1);
            printf("thread1 state is:%d\n",threadstate);
            printf("thread1 stacksize is:%d\n",osThreadGetStackSize(thread1));
            printf("thread1 stackspace is:%d\n",osThreadGetStackSpace(thread1));
            state = osThreadSetPriority(thread1,osPriorityRealtime);
            if (state == osOK)
            {
                printf("thread1 new priority is:%d\n",osThreadGetPriority(thread1));
            }
            printf("thread count is:%d\n",osThreadGetCount());
        }
        else if(10 == count)
        {
            printf("thread2 will yield,thread1 will run!\n");
            osThreadYield();
            printf("thread2 will suspend thread1!\n");
            osThreadSuspend(thread1);
        }
        else if(15 == count)
        {
            printf("thread1 will resume running!\n");
            osThreadResume(thread1);
            printf("thread3 priority is:%d\n",osThreadGetPriority(thread3));
        }
        
        osDelay(3000);
    }
}

void thread3_funct(void* argument)
{

    while(1)
    {
        printf("thread3 running\n");
        
        osDelay(8000);
        
        printf("thread3 will exit!\n");
        
        osThreadExit();
    }
}

void thread4_funct(void* argument)
{
    printf("thread4 running\n");
    
    osDelay(8000);

    printf("thread4 will exit!\n");
}

void thread5_funct(void* argument)
{
    int16_t count = 0;
    while(1)
    {
        count++;
        
        printf("thread5 run: %d \n",count);

        osDelay(3000);
    }
}

int thread_test(void)
{
    osThreadAttr_t thread_attr = {.priority = osPriorityHigh,.attr_bits = osThreadJoinable};

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

    thread3 = osThreadNew(thread3_funct, NULL, &thread_attr);
    if(NULL != thread3)
    {
        printf("thread3 created successfully!\n");
    }
    
    thread4 = osThreadNew(thread4_funct, NULL, &thread_attr);
    if(NULL != thread4)
    {
        printf("thread4 created successfully!\n");
    }
    
    thread5 = osThreadNew(thread5_funct, NULL, &thread_attr);
    if(NULL != thread5)
    {
        printf("thread5 created successfully!\n");
    }
    
    return 0;
}

MSH_CMD_EXPORT(thread_test, sample);


