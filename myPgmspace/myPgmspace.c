/**************************************************************
 * Arduino Bencher
 *
 * @file myPgmspace.c
 *
 * @brief container with functions/variables declarations
 * to store/retrieve data from the program memory space
 *************************************************************/

#include <avr/pgmspace.h>
#include "myGeneratedPgmSpace.h"
#include "myPgmspace.h"

static PGM_P const pgmspace_strings[PGMEM_STR_CNT] PROGMEM = DECLARE_MY_PGMEM;

MY_PGM_P myPgmspace_getDataPointer(uint16_t id)
{
    if ( id < PGMEM_STR_CNT ){
        return (MY_PGM_P)pgm_read_word(&(pgmspace_strings[id]));
    }
    else{
        return 0;
    }
}

uint8_t myPgmspace_copyDataSync(uint16_t id, uint8_t* dest, uint16_t len)
{
    uint16_t pgMemStringSize;

    if ( id < PGMEM_STR_CNT ){
        pgMemStringSize = (uint16_t) pgm_read_dword( &(pgmspace_strings[id][0]) );
        if( len <= pgMemStringSize ){
            strcpy_P( dest, (PGM_P) pgm_read_word( &(pgmspace_strings[id])) );
            return 1;
        }
    }
    return 0;
}


