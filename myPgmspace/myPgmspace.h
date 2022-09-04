
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
 * @name myPgmspace_copyData
 *
 * @brief copy the data to RAM syncronously
 *
 * @arg uint16_t id - id of the data
 *      uint8_t dest - RAM buffer address to copy the data
 *      uint16_t len - size of the buffer
 *
 * @return if operation was successful (buffer is enough)
 *
 *****************************************************/
uint8_t myPgmspace_copyDataSync(uint16_t id, uint8_t* dest, uint16_t len);

#endif /* PGMEM_H */