
/**************************************************************
 * Arduino Bencher
 *
 * @file myPgmspace.h
 *
 * @brief Generated files with big strings/vars, to be used in console
 * UI and pgmSpace
 *************************************************************/
 
#ifndef PGMEM_H
#define PGMEM_H

#include "appTypes.h"
#include <avr/pgmspace.h>
#include "myPgmspaceDefines.h"

#define PGMEM_DATA_START_INDEX 2u
#define PGMEM_SIZE_INDEX 0u


/******************************************************
 * @name myPgmspace_getDataPointer
 *
 * @brief retrieve address of the program memory with the data
 *
 * @arg uint16_t id - id of the data
 *
 * @return PGM_VOID_P pointer
 *
 *****************************************************/
PGM_VOID_P myPgmspace_getDataPointer(uint16_t id);

/******************************************************
 * @name myPgmspace_getDataSize
 *
 * @brief retrieve size of the array given the id
 *
 * @arg uint16_t id - id of the data
 *
 * @return uint16_t size
 *
 *****************************************************/
uint16_t myPgmspace_getDataSize(uint16_t id);

/******************************************************
 * @name myPgmspace_getData
 *
 * @brief retrieve a single byte from the progmem
 *
 * @arg uint8_t address - address of the data
 *
 * @return uint8_t - the data
 *
 *****************************************************/
uint8_t myPgmspace_getData( PGM_VOID_P address );

/******************************************************
 * @name myPgmspace_printSync
 *
 * @brief print the string stored in the memspace
 *
 * @arg uint16_t id - id of the data
 *
 * @return eResult
 *
 *****************************************************/
eResult myPgmspace_printSync(uint16_t id);

/******************************************************
 * @name myPgmspace_printSync
 *
 * @brief print the string stored in the memspace assyncronously
 * needs to be called returns eResult_OK or eResult_NOT_OK
 *
 * @arg uint16_t id - id of the data
 *
 * @return eResult
 *
 *****************************************************/
eResult myPgmspace_printAsync(uint16_t id);

#endif /* PGMEM_H */