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
#include "serialGui.h"
#include "channelInterface.h"

int main(void)
{
    // Initialize tasks
    xTaskCreate(
        TASKCFG_SERIALGUI_TASKFUNCTION,
        TASKCFG_SERIALGUI_NAME,
        TASKCFG_SERIALGUI_STACKSIZE,
        TASKCFG_SERIALGUI_PARAMETERS,
        TASKCFG_SERIALGUI_PRIORITY,
        TASKCFG_SERIALGUI_TASKHANDLE
    );

    xTaskCreate(
        TASKCFG_CHANNELINTERFACE_TASKFUNCTION,
        TASKCFG_CHANNELINTERFACE_NAME,
        TASKCFG_CHANNELINTERFACE_STACKSIZE,
        TASKCFG_CHANNELINTERFACE_PARAMETERS,
        TASKCFG_CHANNELINTERFACE_PRIORITY,
        TASKCFG_CHANNELINTERFACE_TASKHANDLE
    );
}
