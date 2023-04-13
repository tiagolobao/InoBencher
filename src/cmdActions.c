/******************************************************************************************************
 * Arduino Bencher
 *
 * @file cmdActions.c
 *
 * @brief The list of commands/actions is here
 * should be used only inside serialUi context
 ****************************************************************************************************/

#include "FreeRTOS.h"
#include "cmdActions.h"
#include "channelInterface.h"
#include "src/mcurses.h"
#include "myPgmspace.h"
#include "commandProcessorArguments.h"
#include <string.h>

eResult cmd_hi(void);
eResult cmd_dio(void);
eResult cmd_clear(void);
eResult cmd_default(void);
eResult cmd_echo(void);
eResult cmd_vj(void);

const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS] = {
    /* vv don't change default position vv*/
    {"", cmd_default},
    /* ^^ don't change default position ^^ */
    {"hi", cmd_hi},
    {"dio", cmd_dio},
    {"echo", cmd_echo},
    {"clear", cmd_clear},
};


/**************************************************************************************
 * @name echo
 * @arg [0] any string
 * @brief writes in the console anything (test related)
 **************************************************************************************/
#define ECHO_MAX_SIZE 10

eResult cmd_echo(void)
{   
    char strToBePrinted[ECHO_MAX_SIZE];
    eResult res = eResult_NOT_OK;

    res = commandProcessor_getArg_s(0, strToBePrinted, ECHO_MAX_SIZE);
    if ( eResult_OK == res ){
        addstr(strToBePrinted);
        res = eResult_OK;
    }

    return res;
}

/**************************************************************************************
 * @name 
 * @arg no arguments necessary
 * @brief error action
 **************************************************************************************/
eResult cmd_default(void)
{
    return myPgmspace_printAsync(myProgmem_cmdResp_noCommand_id);
}

/**************************************************************************************
 * @name hi
 * @arg no arguments necessary
 * @brief display all possible commands
 **************************************************************************************/
eResult cmd_hi(void)
{
    return myPgmspace_printAsync(myProgmem_cmdResp_hello_id);
}

/**************************************************************************************
 * @name dio
 * @arg [0] action - to read or to write a dio
 * @arg [1] gpio id - (arduino like)
 * @arg [2] action - high or low (only for write)
 * @brief reads or writes a GPIO/DIO pin
 **************************************************************************************/

#define DIO_ARG_ACTION 0
#define DIO_ARG_GPIOID 1
#define DIO_ARG_LEVEL 2

#define ONE_DIGIT_TO_CHAR(d) (char)(d+0x30)

typedef enum{
    dio_getArg = 0,
    dio_waitChannelInterface,
    dio_channelInterfaceRespondedRead,
    dio_Error,
} eDio_state;

eResult cmd_dio(void)
{
    static eDio_state dioState = dio_getArg;
    static dioMsgType dioMsg;

    eResult res = eResult_NOT_OK;
    int gpioId;

    switch(dioState){
    /****** *********************************** *****/
    /******         reading arguments           *****/
    /****** *********************************** *****/
    case dio_getArg:
        // write dio command
        if( eResult_OK == commandProcessor_compArg_s(DIO_ARG_ACTION, "write") ){
            dioMsg.action = DIO_ACTION_WRITE;
            if( eResult_OK == commandProcessor_getArg_d(DIO_ARG_GPIOID, &gpioId) ){    
                dioMsg.gpioId = (uint8_t) gpioId;
                // write high level command
                if( eResult_OK == commandProcessor_compArg_s(DIO_ARG_LEVEL, "high") ){
                    dioMsg.level = DIO_LEVEL_HIGH;
                    res = eResult_PENDING;
                    dioState = dio_waitChannelInterface;
                }
                // write low level command
                else if( eResult_OK == commandProcessor_compArg_s(DIO_ARG_LEVEL, "low") ){
                    dioMsg.level = DIO_LEVEL_LOW;
                    res = eResult_PENDING;
                    dioState = dio_waitChannelInterface;
                }
            }
        }
        // read dio command
        else if( eResult_OK == commandProcessor_compArg_s(DIO_ARG_ACTION, "read") ){
            dioMsg.action = DIO_ACTION_READ;
            if( eResult_OK == commandProcessor_getArg_d(DIO_ARG_GPIOID, &gpioId) ){
                dioMsg.gpioId = (uint8_t) gpioId;
                dioMsg.level = DIO_LEVEL_INVALID;
                res = eResult_PENDING;
                dioState = dio_waitChannelInterface;
            }
        }

        if( eResult_NOT_OK == res ){
            dioState = dio_Error;
            res = eResult_PENDING;
        }
        break;

    /****** *********************************** *****/
    /****** forward command to channelInterface *****/
    /****** *********************************** *****/
    case dio_waitChannelInterface:
        res = channelInterface_receiveDioMessage(&dioMsg);

        switch(res){
            case eResult_PENDING:
                //nothing
                break;
            case eResult_OK:
                dioState = dio_channelInterfaceRespondedRead;
                res = eResult_PENDING;
                break;
            case eResult_NOT_OK:
                dioState = dio_Error;
                res = eResult_PENDING;
                break;
        }
        break;

    /****** *********************************** *****/
    /******           finish command            *****/
    /****** *********************************** *****/
    case dio_channelInterfaceRespondedRead:
        res = myPgmspace_printAsync(myProgmem_cmdResp_dioReadResponse_id);
        if( eResult_OK == res ){
            addch( ONE_DIGIT_TO_CHAR(dioMsg.level) ); 
            addstr("\n\r");
        }
        break;
    case dio_Error:
        res = myPgmspace_printAsync(myProgmem_cmdResp_dioNotPossible_id);
        break;
    }

    if( eResult_PENDING != res )
            dioState = dio_getArg;
    return res;
}

/**************************************************************************************
 * @name clear
 * @arg no arguments necessary
 * @brief clears console
 **************************************************************************************/
eResult cmd_clear(void)
{
    clear();
    move(0,0);
    return eResult_OK;
}