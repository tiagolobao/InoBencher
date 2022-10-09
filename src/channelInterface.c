/**************************************************************
 * Arduino Bencher
 *
 * @file channelInterface.c
 *
 * @brief container with functions related to the control of
 * the GPIO ports (and relays connected)
 *************************************************************/

#include <avr/io.h>
#include "FreeRTOS.h"
#include "appTypes.h"
#include "task.h"
#include "channelInterface.h"
#include "channels_cfg.h"
#include "src/mcurses.h"

#define pcfg portConfigurationArray
#define BLINK_LED_TIMER_ID 0xA1

//-------------------------------------------------------------------------
#define set_bit(temp,bit_num) temp |= 1 << bit_num  // setting this bit in the variable temp
#define clr_bit(temp,bit_num) temp &= ~1 << bit_num // clearing this bit in the variable temp
#define tog_bit(temp,bit_num) temp ^= 1 << bit_num  // toggling this bit in the variable temp
#define get_bit(temp,bit_num) temp &  1 << bit_num // getting this bit in the variable temp

//-------------------------------------------------------------------------
static void ports_init(void)
{
    uint8_t portIndex;

    //The PORTs and DDRs registers starts with 0x00

    // Set the configured ones
    for( portIndex = 0; portIndex < NUMBER_OF_GIPO; portIndex++ ){
        if( pcfg[portIndex].initialportMode != NOT_GPIO ){
            *(pcfg[portIndex].portModeReg) |= (pcfg[portIndex].initialportMode << pcfg[portIndex].gpio_bit);
            *(pcfg[portIndex].portIoReg) |= (pcfg[portIndex].initialValue_isPullup << pcfg[portIndex].gpio_bit);
        }
    }
}

//-------------------------------------------------------------------------
static void dio_write(uint8_t portId, uint8_t value)
{
    if( value ){
        set_bit( *(pcfg[portId].portIoReg) ,pcfg[portId].gpio_bit );
    }
    else{
        clr_bit( *(pcfg[portId].portIoReg) ,pcfg[portId].gpio_bit );
    }
}

//-------------------------------------------------------------------------
static void dio_flip(uint8_t portId)
{
    tog_bit( *(pcfg[portId].portIoReg) ,pcfg[portId].gpio_bit );
}

//-------------------------------------------------------------------------
static uint8_t dio_read(uint8_t portId)
{
    uint8_t l;
    l = get_bit( *(pcfg[portId].portIoReg) ,pcfg[portId].gpio_bit );
    return (l >> pcfg[portId].gpio_bit);
}

//-------------------------------------------------------------------------
static void blinkBuiltinled( uint16_t period, uint16_t taskPeriod )
{
    static uint16_t timerCnt = 0;
    
    if( timerCnt > period ){ // 1 second
        dio_flip(INO_GPIO_13);
        timerCnt = 0;
    }
    timerCnt += taskPeriod;
}

//-------------------------------------------------------------------------
uint8_t channelInterface_getLedState(void)
{
    return dio_read(INO_GPIO_13);
}

//-------------------------------------------------------------------------
void channelInterface_ledFlip(void)
{
    return dio_flip(INO_GPIO_13);
}

//-------------------------------------------------------------------------
eResult channelInterface_receiveDioMessage(dioMsgType *dioMsg)
{

    if( NOT_GPIO == pcfg[dioMsg->gpioId].initialportMode || dioMsg->gpioId >= NUMBER_OF_GIPO )
        return eResult_NOT_OK; // invalid command

    switch(dioMsg->action){
    case DIO_ACTION_WRITE:
        dio_write(dioMsg->gpioId, dioMsg->level);
        break;
    case DIO_ACTION_READ:
        dioMsg->level = dio_read(dioMsg->gpioId);
        break;
    }

    return eResult_OK;
}

//-------------------------------------------------------------------------
void channelInterface_task(void *pvParameters)
{
    TickType_t xPeriod;
    TickType_t xLastWakeTime;
    taskParams *args;
    
    args = (taskParams*)pvParameters;

    xPeriod = pdMS_TO_TICKS(args->taskPeriod);
    xLastWakeTime = xTaskGetTickCount();
    
    // sampling in this task should have constant period

    ports_init();

    for(;;)
    {
        vTaskDelayUntil( &xLastWakeTime, xPeriod );
        // Blink led! I'm alive!
        dio_flip(INO_GPIO_13);
    }
}

