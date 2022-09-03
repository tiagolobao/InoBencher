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
#include "channelInterface.h"
#include "serialGui.h"
#include "uart.h"
#include <string.h>

#define HIGH_SPEED_UART 1
#define BAUD_RATE_UART 115200

void serialGui_task(void *pvParameters)
{
    TickType_t xPeriod;
    TickType_t xLastWakeTime;
    uint16_t a;
    taskParams *args;
    
    args = (taskParams*)pvParameters;

    xPeriod = pdMS_TO_TICKS(args->taskPeriod);
    xLastWakeTime = xTaskGetTickCount();
    
    uart_init(BAUD_RATE_UART,HIGH_SPEED_UART);

    uart_send_string("Hel");    

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, xPeriod );


        //uart_send_string("Hello!");    
        //portStates = channelInterface_getLedState();

        // uart_send_string("\n\rLed state: ");
        // uart_send_byte(portStates+49);

        if( uart_read_count() > 0 )
        {
            a = uart_read();
            if( a == 'z' ){
                uart_send_string("Hello!");
            }
            else{
                uart_send_byte(a);
            }
        }

        if( uart_buffer_full_event() ){
            while( !uart_send_byte('!') );
            while( !uart_send_byte('?') );
        }
    }
}
