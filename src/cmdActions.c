/**************************************************************
 * Arduino Bencher
 *
 * @file cmdActions.c
 *
 * @brief The list of commands/actions is here
 * should be used only inside serialUi context
 *************************************************************/

#include "FreeRTOS.h"
#include "cmdActions.h"
#include "channelInterface.h"
#include "src/mcurses.h"
#include "myPgmspace.h"

extern eResult commandProcessor_getArg_d(const uint8_t p, int *d);
extern eResult commandProcessor_getArg_s(const uint8_t p, char *s, const uint8_t len);

#define ECHO_MAX_SIZE 20

eResult cmd_hi(void);
eResult cmd_dio(void);
eResult cmd_clear(void);
eResult cmd_default(void);
eResult cmd_echo(void);

const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS] = {
    /* vv don't change default position vv*/
    {"", cmd_default},
    /* ^^ don't change default position ^^ */
    {"hi", cmd_hi},
    {"dio", cmd_dio},
    {"echo", cmd_echo},
    {"clear", cmd_clear}
};

eResult cmd_echo(void)
{   
    char strToBePrinted[ECHO_MAX_SIZE];
    eResult res = eResult_NOT_OK;

    if (commandProcessor_getArg_s(0, strToBePrinted, ECHO_MAX_SIZE) ){
        addstr(strToBePrinted);
        res = eResult_OK;
    }

    return res;
}

eResult cmd_default(void)
{
    return myPgmspace_printAsync(myProgmem_cmdResp_noCommand_id);
}

eResult cmd_hi(void)
{
    return myPgmspace_printAsync(myProgmem_cmdResp_hello_id);
}

eResult cmd_dio(void)
{
    eResult result = eResult_NOT_OK;
    channelInterface_ledFlip();
    if(result == eResult_NOT_OK){
        myPgmspace_printAsync(myProgmem_cmdResp_dioNotPossible_id);
    }
    return 0;
}

eResult cmd_clear(void)
{
    clear();
    move(0,0);
    return eResult_OK;
}