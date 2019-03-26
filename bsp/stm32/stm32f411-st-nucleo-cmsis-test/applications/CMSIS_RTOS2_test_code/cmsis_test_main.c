#include <cmsis_os2.h>
#include <stdio.h>
#include "board.h"

extern int  rt_application_init(void);
//extern void kernel_main(void);
//extern void thread_main(void);
//extern void threadflag_main(void);
extern void mutex_main(void);


int main(void)
{
    osKernelInitialize();
    
    rt_application_init();

    
    //kernel_main();
    //thread_main();
    //threadflag_main();
    mutex_main();
    
    osKernelStart();
    
    return 0;
}

