/**************************************************************
 * Arduino Bencher
 *
 * @file serialGui.c
 *
 * @brief container with functions related to the user interface
 * GUI (curses) and CLI
 *************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "serialGui.h"
#include "uart.h"
#include <string.h>

void serialGui_task(void *pvParameters)
{
    TickType_t xPeriod;
    TickType_t xLastWakeTime;

    xPeriod = pdMS_TO_TICKS(1000);
    xLastWakeTime = xTaskGetTickCount();
    
    uart_init(115200,1);

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, xPeriod );
        uart_send_string("Hello world");
    }
}
