/**************************************************************
 * Arduino Bencher
 *
 * @file commandProcessor.c
 *
 * @brief container to manipulate the storage of commands
 * should be used only inside serialUi context
 *************************************************************/

#include "appTypes.h"
#include "commandProcessor.h"
#include "cmdActions.h"
#include "src/mcurses.h"
#include "myPgmspace.h"

static char incommingCommand[MAX_SIZE_COMMAND+1];
static uint8_t commandSize = 0;

actionCallback onGoingCommand = 0;

/* ------------------------------------------------------- */
/*                  LOCAL FUNCTIONS                       */
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
/*                  EXPORTED FUNCTIONS                     */
/* ------------------------------------------------------- */

// ----------------------------------------------------------
uint8_t commandProcessor_append(char c)
{
    if( commandSize < MAX_SIZE_COMMAND ){
        incommingCommand[commandSize] = c;
        commandSize++;
        return true;
    }
    else{
        return false;
    }
}

// ----------------------------------------------------------
uint8_t commandProcessor_remove(void)
{
    if( commandSize>0 ){
        commandSize--;
        return true;
    }
    else{
        return false;
    }
}

// ----------------------------------------------------------
void commandProcessor_clear(void)
{
    commandSize=0;
}

eResult commandProcessor_parse(void)
{
    uint8_t i,j;
    // Linear search, do binary in the future
    for( i=0; i<CMD_NUMBER_OF_ACTIONS; i++ ){
        // Compare strings
        for( j=0; j<commandSize; j++ ){
            if( actionsTable[i].cmdName[j] != incommingCommand[j] )
                break;
        }
        if( j == commandSize ){
            //command found!
            onGoingCommand = actionsTable[i].cb;
            return eResult_OK;
        }
    }
    // no such command
    return eResult_NOT_OK;
}

eResult commandProcessor_commandRun(void)
{
    if( onGoingCommand == 0 )
        return eResult_NOT_OK;
    else
        return onGoingCommand(0);
}