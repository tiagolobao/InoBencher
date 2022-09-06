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
#include "src/mcurses.h"

static const uint8_t* const pgmspace_data[PGMEM_STR_CNT] PROGMEM = DECLARE_MY_PGMEM;
static const uint16_t pgmspace_size[PGMEM_STR_CNT] = DECLARE_MY_PGMEM_SIZES;

#define NO_LAST_ID 0xFFFF

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
eResult myPgmspace_printSync(uint16_t id)
{
    PGM_VOID_P pgmem_c;
    uint16_t pgmem_size;
    uint16_t i;

    pgmem_c = myPgmspace_getDataPointer(id);
    pgmem_size = myPgmspace_getDataSize(id);

    for( i=0; i<pgmem_size; i++,pgmem_c++ ){
        while( !isaddavailable() );
        addch( (uint_fast8_t)myPgmspace_getData(pgmem_c) );
    }

    return eResult_OK;
}

// ----------------------------------------------------------
eResult myPgmspace_printAsync(uint16_t id)
{
    static PGM_VOID_P pgmem_c;
    static uint16_t i;
    static uint16_t pgmem_size;
    static uint16_t lastId = NO_LAST_ID;

    if( NO_LAST_ID == lastId && lastId != id ){
        if( lastId != id ) // not expected ID
            return eResult_NOT_OK;
        // Initialize the variables
        lastId = id;
        i = 0;
        pgmem_c = myPgmspace_getDataPointer(id);
        pgmem_size = myPgmspace_getDataSize(id);
    }

    // read array in the progmeme
    for( ; i<pgmem_size && isaddavailable(); i++,pgmem_c++ ){
        addch( (uint_fast8_t)myPgmspace_getData(pgmem_c) );
    }

    // check if read is complete
    if( i == pgmem_size ){
        lastId = NO_LAST_ID;
        return eResult_OK;
    }
    
    return eResult_PENDING;
}

