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

// ------ CHARACTER DEFINITIONS ------
#define ASCII_BEL 0x07
#define ASCII_BACKSPACE 0x08
#define ASCII_CR 0x0D
#define ASCII_SPACE 0x20
#define ASCII_DEL 0x7F
#define ASCII_ESCAPE 0x1B
#define ASCII_VISIBLE_CHAR_MIN 0x21
#define ASCII_VISIBLE_CHAR_MAX 0x7E

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
static void printStart(void)
{
    uart_send_string( myPgmspace_getDataPointer(0) );
}

// ----------------------------------------------------------
static void printNewLine(void)
{
    uart_send_byte('\n');
#if (IS_CRLF == 1)
    uart_send_byte('\r');
#endif
    uart_send_byte('>');
    uart_send_byte(' ');
}

// ----------------------------------------------------------
static uint8_t isIdleConnection(void)
{
    return (uart_read_count() == 0);
}

// ----------------------------------------------------------
static void processCommand(void)
{
    if(strcmp(incommingCommand,"hi") == 0){
        uart_send_string("\n\rHello :)");
        printNewLine();
    }
    else{
        uart_send_string("\n\rCommand not recognized");
        uart_send_string("\n\rit was: ");
        uart_send_string(incommingCommand);
        printNewLine();
    }
    clearCommand();
}

// ----------------------------------------------------------
static void processInput(void)
{
    uint8_t input = UI_NO_INPUT;

    // The limit of reads per cycle are now defined by RX_BUFFER_SIZE
    // Check uart.h to configure it
    while( uart_read_count() > 0 )
    {
        input = uart_read();
        if( isVisibleChar(input) )
        {
            if( appendToCommand(input) ){
                uart_send_byte(input);
            }
            else{
                uart_send_byte(ASCII_BEL);
            }
        }
        else
        {
            switch (input){
                case ASCII_BACKSPACE:
                    if( deleteFromCommand() )
                        uart_send_byte(ASCII_DEL);
                    else
                        uart_send_byte(ASCII_BEL);
                    break;
                case ASCII_CR:
                    appendToCommand('\0');
                    uiState = SerialUi_PortConnectedDoCommand;
                    break;
                case ASCII_SPACE:
                    if( appendToCommand(input) ){
                        uart_send_byte(input);
                    }
                    else{
                        uart_send_byte(ASCII_BEL);
                    }
                    break;
                case ASCII_ESCAPE:
                    //snprintf( incommingCommand, MAX_SIZE_COMMAND, "received %x \n\r",input );
                    //uart_send_string(input);
                    break;
                default:
                    // not a valid char!
                    break;
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
            if( isIdleConnection() ){
                break;
            }
            else{
                uiState = SerialUi_PortConnectedListening;
                if( OK == buffStatus ){
                    printStart();
                    uart_flush();
                }
                else{
                    uart_send_string("curses init error!");
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
