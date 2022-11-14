/**************************************************************
 * Arduino Bencher
 *
 * @file cmdActions.h
 *
 * @brief The list of commands/actions is here
 *************************************************************/

#include "appTypes.h"

typedef eResult (*actionCallback)(void);

typedef struct{
    char* cmdName;
    actionCallback cb;
} actionNode;

#define CMD_NUMBER_OF_ACTIONS 6
#define CMD_ACTION_ID_DEFAULT 0

extern const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS];