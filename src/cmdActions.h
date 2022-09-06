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

#define CMD_NUMBER_OF_ACTIONS 2
extern const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS];