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
#include "myPgmspace.h"
#include "heaplessLinkedList.h"

// chars ASCII
#define ASCII_SPACE ' '
#define ASCII_STR_END '\0'

// limitation due to atmega small ram size
#define MAX_SIZE_COMMAND 50
//#define MAX_NUMBER_OF_ARGS 8

// do not operate those directly
static tIndex __ringBufferArray__[MAX_SIZE_COMMAND];
static heaplessListNode __heapArray__[MAX_SIZE_COMMAND];

// internal variables
static heaplessList incommingCommand;
static actionCallback onGoingCommand = NULL;

/* ------------------------------------------------------- */
/*                  LOCAL FUNCTIONS - Linked list          */
/* ------------------------------------------------------- */



/* ------------------------------------------------------- */
/*                  EXPORTED FUNCTIONS                     */
/* ------------------------------------------------------- */

void commandProcessor_Init(void)
{
    heaplessList_init(&incommingCommand, __ringBufferArray__, __heapArray__, MAX_SIZE_COMMAND);
}
// ----------------------------------------------------------
uint8_t commandProcessor_append(char c)
{
    return heaplessList_append(&incommingCommand, c);
}

// ----------------------------------------------------------
uint8_t commandProcessor_remove(void)
{
    return heaplessList_removeLast(&incommingCommand);
}

// ----------------------------------------------------------
void commandProcessor_clear(void)
{
    while(heaplessList_removeFirst(&incommingCommand));
}

eResult commandProcessor_parse(void)
{
    uint8_t i,j;
    heaplessListNode *it;
    // Linear search, do binary in the future
    for( i=1; i<CMD_NUMBER_OF_ACTIONS; i++ ){
        // Compare command strings
        j=0;
        it = heaplessList_initIt(&incommingCommand);
        while( actionsTable[i].cmdName[j] != ASCII_STR_END ){
            if( actionsTable[i].cmdName[j] != heaplessList_getItData(it) )
                break;
            j++;
            heaplessList_nextIt(&incommingCommand,&it);
        }
        if( actionsTable[i].cmdName[j] == ASCII_STR_END){
            //command found! Parse arguments
            onGoingCommand = actionsTable[i].cb;
            return eResult_OK;
        }
    }
    // no such command
    onGoingCommand = actionsTable[CMD_ACTION_ID_DEFAULT].cb;

    return eResult_OK;
}

// ----------------------------------------------------------
eResult commandProcessor_commandRun(void)
{
    if( onGoingCommand == NULL )
        return eResult_NOT_OK;
    else
        return onGoingCommand(NULL);
}
