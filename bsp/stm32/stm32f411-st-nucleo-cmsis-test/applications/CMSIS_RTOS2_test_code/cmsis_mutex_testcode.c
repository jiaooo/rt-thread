#include <stdio.h>
#include <cmsis_os2.h>

/* 线程控制块 */
static osThreadId_t thread1;
static osThreadId_t thread2;

static osMutexId_t mutex_id;

/* 线程共享的打印函数 */
static void printer(char* str)
{
	while(*str != 0)
	{
		putchar(*str);	/* 输出一个字符 */
		str++;
        osDelay(100);	/* 休眠1秒 */
	}
	printf("\n");
}

void thread1_funct(void* argument)
{
    osStatus_t result;
    char* str = "thread1 hello RT-Thread";
    
    while(1)
    {
        printf("thread1 try to acquire mutex!\n");
        
		result = osMutexAcquire(mutex_id,osWaitForever);	  /* 互斥锁上锁 */
		if (osOK == result)
        {
            printer(str);  /* 访问共享打印函数 */
        }
		else
        {
            printf("acquire mutex failed!error code is:%d\n",result);
        }
		
		result = osMutexRelease(mutex_id);  /* 访问完成后解锁 */
        if (osOK != result)
        {
            printf("release mutex failed!error code is:%d\n",result);
        }

        osDelay(3000);
    }
}

void thread2_funct(void* argument)
{
    char* str = "thread2 hi world";
    osStatus_t result;

    
    while(1)
    {
        printf("thread2 try to acquire mutex!\n");
		result = osMutexAcquire(mutex_id,osWaitForever);  /* 互斥锁上锁 */
		if (osOK == result)
        {
            printer(str);  /* 访问共享打印函数 */
        }
		else
        {
            printf("acquire mutex failed!error code is:%d\n",result);
        }
		
		result = osMutexRelease(mutex_id);  /* 访问完成后解锁 */
        if (osOK != result)
        {
            printf("release mutex failed!error code is:%d\n",result);
        }

        osDelay(3000);
    }
}

void mutex_main(void)
{
	osThreadAttr_t thread1_attr = {.priority = osPriorityHigh};
    osThreadAttr_t thread2_attr = {.priority = osPriorityHigh4};
    const osMutexAttr_t Mutex_attr = {"myThreadMutex",osMutexRecursive,NULL,NULL};
    
    mutex_id = osMutexNew(&Mutex_attr);
	if(mutex_id != NULL)
    {
        printf("mutex new ok!\n");
    }
    else
    {
        printf("mutex new failed!\n");
    }
	
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


}

