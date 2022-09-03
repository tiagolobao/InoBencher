
/***************************
 * SERIAL UI CONFIGURATION
 ***************************/

#ifndef TASKS_CFG_H
#define TASKS_CFG_H

#include "appTypes.h"

// app config
#define TASKCFG_SERIALUI_PERIOD_MS         20u
const taskParams cArg_serialUi = {
    TASKCFG_SERIALUI_PERIOD_MS 
};

// os config
#define TASKCFG_SERIALUI_STACKSIZE         0x100
#define TASKCFG_SERIALUI_TASKFUNCTION      serialUi_task
#define TASKCFG_SERIALUI_NAME              "serialUI"
#define TASKCFG_SERIALUI_PARAMETERS        (void*)&cArg_serialUi
#define TASKCFG_SERIALUI_PRIORITY          2
#define TASKCFG_SERIALUI_TASKHANDLE        NULL    

/**********************************
 * CHANNEL INTERFACE CONFIGURATION
 *********************************/
//app config
#define TASKCFG_CHANNELINTERFACE_PERIOD_MS         500u
const taskParams cArg_channelInterface = {
    TASKCFG_CHANNELINTERFACE_PERIOD_MS 
};

//os config
#define TASKCFG_CHANNELINTERFACE_STACKSIZE         0x100
#define TASKCFG_CHANNELINTERFACE_TASKFUNCTION      channelInterface_task
#define TASKCFG_CHANNELINTERFACE_NAME              "channelInterface"
#define TASKCFG_CHANNELINTERFACE_PARAMETERS        (void*)&cArg_channelInterface
#define TASKCFG_CHANNELINTERFACE_PRIORITY          1
#define TASKCFG_CHANNELINTERFACE_TASKHANDLE        NULL    

#endif /* TASKS_CFG_H */