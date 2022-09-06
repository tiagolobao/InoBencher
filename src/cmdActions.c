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

eResult cmd_hi(void* args);
eResult cmd_dio(void* args);
eResult cmd_clear(void* args);
eResult cmd_default(void* args);

const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS] = {
    {"", cmd_default},
    {"hi", cmd_hi},
    {"dio", cmd_dio},
    {"clear", cmd_clear}
};

eResult cmd_default(void* args)
{
    return myPgmspace_printSync(myProgmem_cmdResp_noCommand_id);
}

eResult cmd_hi(void* args)
{
    return myPgmspace_printAsync(myProgmem_cmdResp_hello_id);
}

eResult cmd_dio(void* args)
{
    eResult result = eResult_NOT_OK;
    channelInterface_ledFlip();
    if(result == eResult_NOT_OK){
        myPgmspace_printSync(myProgmem_cmdResp_dioNotPossible_id);
    }
    return 0;
}

eResult cmd_clear(void* args)
{
    clear();
    move(0,0);
    return eResult_OK;
}