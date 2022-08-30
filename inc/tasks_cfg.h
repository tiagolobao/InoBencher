
/***************************
 * SERIAL GUI CONFIGURATION
 ***************************/

#ifndef TASKS_CFG_H
#define TASKS_CFG_H

#include "appTypes.h"

// app config
#define TASKCFG_SERIALGUI_PERIOD_MS         30u
const taskParams cArg_serialGui = {
    TASKCFG_SERIALGUI_PERIOD_MS 
};

// os config
#define TASKCFG_SERIALGUI_STACKSIZE         0x80
#define TASKCFG_SERIALGUI_TASKFUNCTION      serialGui_task
#define TASKCFG_SERIALGUI_NAME              "serialGui"
#define TASKCFG_SERIALGUI_PARAMETERS        (void*)&cArg_serialGui 
#define TASKCFG_SERIALGUI_PRIORITY          1
#define TASKCFG_SERIALGUI_TASKHANDLE        NULL    

/**********************************
 * CHANNEL INTERFACE CONFIGURATION
 *********************************/
//app config
#define TASKCFG_CHANNELINTERFACE_PERIOD_MS         10u
const taskParams cArg_channelInterface = {
    TASKCFG_CHANNELINTERFACE_PERIOD_MS 
};

//os config
#define TASKCFG_CHANNELINTERFACE_STACKSIZE         0x80
#define TASKCFG_CHANNELINTERFACE_TASKFUNCTION      channelInterface_task
#define TASKCFG_CHANNELINTERFACE_NAME              "channelInterface"
#define TASKCFG_CHANNELINTERFACE_PARAMETERS        (void*)&cArg_channelInterface
#define TASKCFG_CHANNELINTERFACE_PRIORITY          2
#define TASKCFG_CHANNELINTERFACE_TASKHANDLE        NULL    

#endif /* TASKS_CFG_H */