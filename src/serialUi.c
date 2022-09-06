/**************************************************************
 * Arduino Bencher
 *
 * @file serialGui.c
 *
 * @brief container with functions related to the user interface
 * UI (curses) and CLI
 *************************************************************/

#include "appTypes.h"
#include "FreeRTOS.h"
#include "task.h"
#include "serialUi.h"
#include "src/mcurses.h"
#include "commandProcessor.h"
#include "myPgmspace.h"

// ------ TYPE DEFINITIONS ------
typedef enum{
    SerialUi_NoConnection = 0,
    SerialUi_PortConnectedListening,
    SerialUi_PortConnectedParseCommand,
    SerialUi_commandOngoing
} eSerialUi_state;

// ------ CONST DEFINITIONS ------
#define IS_CRLF 1

// --- LOCAL VARIABLES DEFINITIONS ----
static eSerialUi_state uiState = SerialUi_NoConnection;

// ------ FUNCTIONS -------------------

// ----------------------------------------------------------
static void printNewLine(void)
{
#if (IS_CRLF == 1)
    addch(ASCII_NEWLINE);
#endif
    addch(KEY_CR);
}


static void printNewLineCommand(void)
{
    printNewLine();
    addch('>');
    addch(' ');
}

static void triggerCommand(void)
{
    eResult r;

    r = commandProcessor_commandRun();
    if( r == eResult_OK )
        uiState = SerialUi_PortConnectedListening;   
    // else keep running the action
}

// ----------------------------------------------------------
static void parseCommand(void)
{
    printNewLine();

    if( eResult_NOT_OK == commandProcessor_parse() ){
        myPgmspace_printSync(myProgmem_cmdResp_noCommand_id);
        addstr("~~");
        uiState = SerialUi_PortConnectedListening;   
    }
    else{
        uiState = SerialUi_commandOngoing;
    }

    commandProcessor_clear();
    printNewLineCommand();
    
}

// ----------------------------------------------------------
static void inputListen(void)
{
    uint8_t input;
    uint_fast8_t y,x;

    // The limit of reads per cycle are now defined by RX_BUFFER_SIZE
    // Check uart.h to configure it. Don't put too low, otherwise the
    // getch won't work properly!
    while( isgetavailable() )
    {
        input = getch();
        switch(input)
        {
        case KEY_BACKSPACE:
            if( commandProcessor_remove() ){
                getyx(y,x);
                move(y,(x-1));
                delch();
            }
            else{
                addch(ASCII_BEL);
            }
            break;
        
        case KEY_CR:
            commandProcessor_append((char)ASCII_NUL);
            uiState = SerialUi_PortConnectedParseCommand;
            break;

        case KEY_DOWN:
            // not implemented
            break;
        case KEY_UP:
            // not implemented
            break;
        case KEY_LEFT:
            // not implemented
            break;
        case KEY_RIGHT:
            // not implemented
            break;
        case KEY_HOME:
            // not implemented
            break;

        default:
            if( commandProcessor_append((char)input) ){
                addch(input);
            }
            else{
                addch(ASCII_BEL);
            }
          
        } /* switch end */
    } /* while end */
}

// ----------------------------------------------------------
static void idleUi(void)
{
    
    if( isgetavailable() ){
        myPgmspace_printSync(myProgmem_startMessage_id);
        refresh();
        printNewLineCommand();
        uiState = SerialUi_PortConnectedListening;
    }
}

// ----------------------------------------------------------
void serialUi_task(void *pvParameters)
{
    TickType_t xPeriod;
    TickType_t xLastWakeTime;
    taskParams *args;

    args = (taskParams*)pvParameters;

    xPeriod = pdMS_TO_TICKS(args->taskPeriod);
    xLastWakeTime = xTaskGetTickCount();

    initscr();

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, xPeriod );

        // State machine
        switch(uiState){
        case SerialUi_NoConnection:
            idleUi();
            break;
        case SerialUi_PortConnectedListening:
            inputListen();
            break;
        case SerialUi_PortConnectedParseCommand:
            parseCommand();
            break;
        case SerialUi_commandOngoing:
            triggerCommand();
            break;
        default:
            // not expected
            break;
        } /* switch state machine */
    } /* task loop */
}
