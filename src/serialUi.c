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
#include "uart.h"
#include <string.h>

// ------ PROGMEM DEFINITIONS ------
#include <avr/pgmspace.h>

// big array of strings
const char string_1[] PROGMEM = "serialUi started!\n\r";
const char string_2[] PROGMEM = "Welcome to Arduino Bencher\n\r";
const char string_3[] PROGMEM = "By: Tiago Lobao\n\r";
const char string_4[] PROGMEM = "> ";

PGM_P const pgmspace_strings[] PROGMEM = 
{
    string_1,
    string_2,
    string_3,
    string_4
};


// ------ TYPE DEFINITIONS ------
typedef enum{
    SerialUi_NoConnection = 0,
    SerialUi_PortConnectedListening,
    SerialUi_PortConnectedDoCommand
} eSerialUi_state;

// ------ CONST DEFINITIONS ------
#define HIGH_SPEED_UART 1
#define BAUD_RATE_UART 115200
#define IS_CRLF 1

#define UI_NO_INPUT 0xFF
#define MAX_SIZE_COMMAND 32u

// ------ CHARACTER DEFINITIONS ------
#define ASCII_BACKSPACE 0x08
#define ASCII_CR 0x0D
#define ASCII_SPACE 0x20
#define ASCII_DEL 0x7F
#define ASCII_ESCAPE 0x1B
#define ASCII_VISIBLE_CHAR_MIN 0x21
#define ASCII_VISIBLE_CHAR_MAX 0x7E


// ------ LOCAL VARIABLES DEFINITIONS -
static unsigned char incommingCommand[MAX_SIZE_COMMAND];
static uint8_t commandSize = 0;

static eSerialUi_state uiState = SerialUi_NoConnection;

// ------ MACROS ----------------------
#define isVisibleChar(c) (ASCII_VISIBLE_CHAR_MIN<=c && c<=ASCII_VISIBLE_CHAR_MAX)

// ------ FUNCTIONS -------------------

// ----------------------------------------------------------
static void appendToCommand(unsigned c)
{
    incommingCommand[commandSize] = c;
    commandSize++;
}

// ----------------------------------------------------------
static void deleteFromCommand(void)
{
    if( commandSize>0 )
        commandSize--;
}

// ----------------------------------------------------------
static void clearCommand(void)
{
    commandSize=0;
}


// ----------------------------------------------------------
static void printStart(void)
{
    char buffString[32];
    strcpy_P( buffString, (PGM_P)pgm_read_word(&(pgmspace_strings[0])) );
    uart_send_string(buffString);
    strcpy_P( buffString, (PGM_P)pgm_read_word(&(pgmspace_strings[1])) );
    uart_send_string(buffString);
    strcpy_P( buffString, (PGM_P)pgm_read_word(&(pgmspace_strings[2])) );
    uart_send_string(buffString);
    strcpy_P( buffString, (PGM_P)pgm_read_word(&(pgmspace_strings[3])) );
    uart_send_string(buffString);
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

    // debug from command sessions
    //snprintf( incommingCommand, MAX_SIZE_COMMAND, "received %x \n\r",input );
    //uart_send_string(input);

    // The limit of reads per cycle are now defined by RX_BUFFER_SIZE
    // Check uart.h to configure it
    while( uart_read_count() > 0 )
    {
        input = uart_read();
        if( isVisibleChar(input) )
        {
            appendToCommand(input);
            uart_send_byte(input);
        }
        else
        {
            switch (input){
                case ASCII_BACKSPACE:
                    deleteFromCommand();
                    uart_send_byte(input);
                    break;
                case ASCII_CR:
                    uiState = SerialUi_PortConnectedDoCommand;
                    break;
                case ASCII_SPACE:
                    appendToCommand(input);
                    uart_send_byte(input);
                    break;
                case ASCII_DEL:
                    //not implemented yet
                    break;
                case ASCII_ESCAPE:
                    //not implemented yet
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
    
    args = (taskParams*)pvParameters;

    xPeriod = pdMS_TO_TICKS(args->taskPeriod);
    xLastWakeTime = xTaskGetTickCount();
    
    uart_init(BAUD_RATE_UART,HIGH_SPEED_UART);

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
                printStart();
                uart_flush();
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
