/**************************************************************
 * Arduino Bencher
 *
 * @file cmdActions.h
 *
 * @brief The list of commands/actions is here
 *************************************************************/

#include "appTypes.h"

typedef eResult (*actionCallback)(void* args);

typedef struct{
    char* cmdName;
    actionCallback cb;
} actionNode;

#define CMD_NUMBER_OF_ACTIONS 4
#define CMD_ACTION_ID_DEFAULT 0

extern const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS];