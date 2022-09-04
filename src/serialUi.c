/**************************************************************
 * Arduino Bencher
 *
 * @file serialGui.c
 *
 * @brief container with functions related to the user interface
 * GUI (curses) and CLI
 *************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "channelInterface.h"
#include "serialUi.h"
#include "drivers/atmega328p/uart.h"
#include "src/mcurses.h"
#include <string.h>
#include "myPgmspace.h"


// ------ TYPE DEFINITIONS ------
typedef enum{
    SerialUi_NoConnection = 0,
    SerialUi_PortConnectedListening,
    SerialUi_PortConnectedDoCommand
} eSerialUi_state;

// ------ CONST DEFINITIONS ------
#define IS_CRLF 1

#define UI_NO_INPUT 0xFF
#define MAX_SIZE_COMMAND 32u

// ------ SEQUENCE DEFINITIONS ------
#define SEQ_DELCH PSTR("\033[P")  // delete character
#define SIZE_DELCH    (6u)

#define SEQ_CLEAR PSTR("\033[2J")  // clear screen
#define SIZE_DELCH    (6u) 


// ------ LOCAL VARIABLES DEFINITIONS -
static unsigned char incommingCommand[MAX_SIZE_COMMAND+1];
static uint8_t commandSize = 0;

static eSerialUi_state uiState = SerialUi_NoConnection;

// ------ MACROS ----------------------
#define isVisibleChar(c) (ASCII_VISIBLE_CHAR_MIN<=c && c<=ASCII_VISIBLE_CHAR_MAX)

// ------ FUNCTIONS -------------------

// ----------------------------------------------------------
static uint8_t appendToCommand(unsigned c)
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
static uint8_t deleteFromCommand(void)
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
static void clearCommand(void)
{
    commandSize=0;
}


// ----------------------------------------------------------
static void printSyncfromPrgMemory(uint16_t id)
{
    PGM_VOID_P pgmem_c;
    uint16_t pgmem_size;
    uint16_t i;

    pgmem_c = myPgmspace_getDataPointer(myProgmem_startMessage_id);
    pgmem_size = myPgmspace_getDataSize(myProgmem_startMessage_id);

    for( i=0; i<pgmem_size; i++,pgmem_c++ ){
        addch( (uint_fast8_t)myPgmspace_getData(pgmem_c) );
    }
}

// ----------------------------------------------------------
static void printNewLine(void)
{
    addch('\n');
#if (IS_CRLF == 1)
    addch('\r');
#endif
    addch('>');
    addch(' ');
}

// ----------------------------------------------------------
static void processCommand(void)
{
    if(commandSize == 0){
        printNewLine();
    }
    else if(strcmp(incommingCommand,"hi") == 0){
        addstr("\n\rHello :)");
        
    }
    else if(strcmp(incommingCommand,"dbg") == 0){
        char bffr[50];
        uint_fast8_t y,x;
        getyx(y,x);
        sprintf(bffr,"\n\r%d, %d",x,y);
        addstr(bffr);
        getyx(y,x);
        sprintf(bffr,"\n\r%d, %d",x,y);
        addstr(bffr);
    }
    else{
        addstr("\n\rCommand not recognized");
        addstr("\n\rit was: ");
        addstr(incommingCommand);
    }
    printNewLine();
    clearCommand();
}

// ----------------------------------------------------------
static void processInput(void)
{
    uint8_t input = UI_NO_INPUT;

    // The limit of reads per cycle are now defined by RX_BUFFER_SIZE
    // Check uart.h to configure it
    while( isgetavailable() )
    {
        input = getch();
        switch(input)
        {
        case KEY_BACKSPACE:
            if( deleteFromCommand() ){
                uint_fast8_t y,x;
                getyx(y,x);
                move(y,(x-1));
                delch();
            }
            else{
                addch(ASCII_BEL);
            }
            break;
        
        case KEY_CR:
            appendToCommand('\0');
            uiState = SerialUi_PortConnectedDoCommand;
            break;
        default:
            if( appendToCommand(input) ){
                addch(input);
            }
            else{
                addch(ASCII_BEL);
            }
            
        }
    }
}

// ----------------------------------------------------------
void serialUi_task(void *pvParameters)
{
    TickType_t xPeriod;
    TickType_t xLastWakeTime;
    taskParams *args;
    uint8_t buffStatus;

    args = (taskParams*)pvParameters;

    xPeriod = pdMS_TO_TICKS(args->taskPeriod);
    xLastWakeTime = xTaskGetTickCount();
    
    buffStatus = initscr();

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, xPeriod );
        // State machine
        switch(uiState){
        case SerialUi_NoConnection:
            if( isgetavailable() ){
                break;
            }
            else{
                uiState = SerialUi_PortConnectedListening;
                if( OK == buffStatus ){
                    printSyncfromPrgMemory(myProgmem_startMessage_id);
                    printNewLine();
                    uart_flush();
                }
                else{
                    addstr("curses init error!");
                    uiState = SerialUi_NoConnection;
                }
            }
        case SerialUi_PortConnectedListening:
            processInput();
            break;
        case SerialUi_PortConnectedDoCommand:
            processCommand();
            uiState = SerialUi_PortConnectedListening;
            break;
        default:
            // not expected
            break;
        }
    }
}
