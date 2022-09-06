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

const actionNode actionsTable[CMD_NUMBER_OF_ACTIONS] = {
    {"hi", cmd_hi},
    {"dio", cmd_dio}
};

eResult cmd_hi(void* args)
{
    return myPgmspace_printSync(myProgmem_cmdResp_hello_id);
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