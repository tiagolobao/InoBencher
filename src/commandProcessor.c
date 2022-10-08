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
#include <stdlib.h>
#include "src/mcurses.h"

// chars ASCII
#define ASCII_SPACE ' '
#define ASCII_STR_END '\0'
#define ASCII_MIN_NUMERAL 0x30
#define ASCII_MAX_NUMERAL 0x39
// #define ASCII_MIN_PRINTABLE 0x21
// #define ASCII_MAX_PRINTABLE 0x7E

// limitation due to atmega small ram size
#define MAX_SIZE_COMMAND 50
#define MAX_NUMBER_OF_ARGS 4
#define MAX_SIZE_OF_NUMBER_ARG 4

// do not operate those directly
static tIndex __ringBufferArray__[MAX_SIZE_COMMAND];
static heaplessListNode __heapArray__[MAX_SIZE_COMMAND];

// internal variables
static heaplessList incommingCommand;
static actionCallback onGoingCommand = NULL;

static heaplessListNode* argStartNodes[MAX_NUMBER_OF_ARGS];
static uint8_t argCount;


/* ------------------------------------------------------- */
/*                  EXPORTED FUNCTIONS                     */
/* ------------------------------------------------------- */

void commandProcessor_Init(void)
{
    heaplessList_init(&incommingCommand, __ringBufferArray__, __heapArray__, MAX_SIZE_COMMAND);
    commandProcessor_clear();
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
    uint16_t i;
    while(heaplessList_removeFirst(&incommingCommand));
    for(i=0;i<MAX_NUMBER_OF_ARGS;i++)
        argStartNodes[i] = NULL;
    argCount = 0;
}

eResult commandProcessor_parse(void)
{
    uint8_t i,j;
    heaplessListNode *it;
    char lastChar;

    // Linear search, do binary in the future
    for( i=1; i<CMD_NUMBER_OF_ACTIONS; i++ ){
        // Compare command strings
        j=0;
        it = heaplessList_initIt(&incommingCommand);
        while( actionsTable[i].cmdName[j] != ASCII_STR_END || heaplessList_getItData(it) != ASCII_STR_END ){
            if( actionsTable[i].cmdName[j] != heaplessList_getItData(it) )
                break;
            j++;
            heaplessList_nextIt(&incommingCommand,&it);
        }

        lastChar = heaplessList_getItData(it);
        if( 
            ( actionsTable[i].cmdName[j] == ASCII_STR_END ) &&
            ( lastChar == ASCII_STR_END || lastChar == ASCII_SPACE )
        ){
            //command found! Parse arguments
            while( heaplessList_getItData(it) != ASCII_STR_END ){
                if( lastChar == ASCII_SPACE && heaplessList_getItData(it) != ASCII_SPACE ){
                    //beginning of an argument
                    argStartNodes[argCount] = it;
                    argCount++;
                    if( argCount == MAX_NUMBER_OF_ARGS ){
                        // ignore further args
                        break;
                    }
                }                
                lastChar = heaplessList_getItData(it);
                heaplessList_nextIt(&incommingCommand,&it);
            }
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
        return onGoingCommand();
}

// ----------------------------------------------------------
eResult commandProcessor_getArg_d(const uint8_t p, int *d)
{
    char s[MAX_SIZE_OF_NUMBER_ARG+1];
    uint8_t cnt = 0;
    heaplessListNode* it = argStartNodes[p];
    char c;

    if( p >= argCount )
        return eResult_NOT_OK;
    
    while( it != NULL && cnt < MAX_SIZE_OF_NUMBER_ARG && heaplessList_getItData(it) != ASCII_SPACE ){

        c = heaplessList_getItData(it);
        if( c < ASCII_MIN_NUMERAL || c > ASCII_MAX_NUMERAL )
            return eResult_NOT_OK;

        s[cnt] = c;
        heaplessList_nextIt(&incommingCommand, &it);
        cnt++;
    } 
    

    s[cnt] = ASCII_STR_END;
    *d = atoi(s);

    return eResult_OK;
}

// ----------------------------------------------------------
eResult commandProcessor_getArg_s(const uint8_t p, char *s, const uint8_t len)
{
    heaplessListNode* it;
    uint8_t cnt = 0;

    if( p >= argCount )
        return eResult_NOT_OK;

    it = argStartNodes[p];
    while( it != NULL && heaplessList_getItData(it) != ASCII_SPACE ){

        if( cnt >= len )
            return eResult_NOT_OK;

        s[cnt] = heaplessList_getItData(it);
        heaplessList_nextIt(&incommingCommand,&it);
        cnt++;
    }

    return eResult_OK;
}