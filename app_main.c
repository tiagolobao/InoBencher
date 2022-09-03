/**************************************************************
 * Arduino Bencher
 *
 * @file app_main.c
 *
 * @brief Main file of the project contain definition of the 
 * tasks and pre-init commands
 *************************************************************/


#include "FreeRTOS.h"
#include "task.h"
#include "tasks_cfg.h"
#include "serialUi.h"
#include "channelInterface.h"
#include <avr/io.h>

int main(void)
{

    // Initialize tasks
    xTaskCreate(
        TASKCFG_SERIALUI_TASKFUNCTION,
        TASKCFG_SERIALUI_NAME,
        TASKCFG_SERIALUI_STACKSIZE,
        TASKCFG_SERIALUI_PARAMETERS,
        TASKCFG_SERIALUI_PRIORITY,
        TASKCFG_SERIALUI_TASKHANDLE
    );

    xTaskCreate(
        TASKCFG_CHANNELINTERFACE_TASKFUNCTION,
        TASKCFG_CHANNELINTERFACE_NAME,
        TASKCFG_CHANNELINTERFACE_STACKSIZE,
        TASKCFG_CHANNELINTERFACE_PARAMETERS,
        TASKCFG_CHANNELINTERFACE_PRIORITY,
        TASKCFG_CHANNELINTERFACE_TASKHANDLE
    );

    vTaskStartScheduler();
}
