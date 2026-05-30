


#include <stdint.h>
#include "uart.h"
#include "systemspecific.h"



int main(void)
{
    UART2_Init();

    while(1)
    {

        UART2_WriteString("Hello from STM32\r\n");

        for(volatile int i = 0; i < 1000000; i++);
    }
}
