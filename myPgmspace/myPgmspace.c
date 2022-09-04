/**************************************************************
 * Arduino Bencher
 *
 * @file myPgmspace.c
 *
 * @brief container with functions/variables declarations
 * to store/retrieve data from the program memory space
 *************************************************************/

#include "myPgmspace.h"
#include "myGeneratedPgmSpace.h"

static const uint8_t* const pgmspace_data[PGMEM_STR_CNT] PROGMEM = DECLARE_MY_PGMEM;
static const uint16_t pgmspace_size[PGMEM_STR_CNT] = DECLARE_MY_PGMEM_SIZES;

// ----------------------------------------------------------
PGM_VOID_P myPgmspace_getDataPointer(uint16_t id)
{
    if ( id < PGMEM_STR_CNT ){
        return (PGM_VOID_P) pgm_read_word(&pgmspace_data[id]); 
    }
    else{
        return 0;
    }
}

// ----------------------------------------------------------
uint16_t myPgmspace_getDataSize(uint16_t id)
{
    return pgmspace_size[id];
}

// ----------------------------------------------------------
uint8_t myPgmspace_getData( PGM_VOID_P address )
{
    return pgm_read_byte(address);
}

// ----------------------------------------------------------
uint8_t myPgmspace_copyDataSync(uint16_t id, uint8_t* dest, uint16_t len)
{
    uint16_t pgMemStringSize;

    return 0;
    /* not implemented
    if ( id < PGMEM_STR_CNT ){
        pgMemStringSize = (uint16_t) pgm_read_dword( &(pgmspace_data[id]) );
        if( len <= pgMemStringSize ){
            strcpy_P( (char*)dest, (PGM_VOID_P) pgm_read_word( &(pgmspace_data[id])) );
            return 1;
        }
    }
    return 0;
    */
}


