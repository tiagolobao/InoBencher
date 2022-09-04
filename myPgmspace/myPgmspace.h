
/**************************************************************
 * Arduino Bencher
 *
 * @file myPgmspace.h
 *
 * @brief Generated files with big strings/vars, to be used in console
 * UI and pgmSpace
 *************************************************************/
 
#ifndef PGMEM_SHARE_H
#define PGMEM_SHARE_H

typedef unsigned char* MY_PGM_P;

/******************************************************
 * @name myPgmspace_getDataPointer
 *
 * @brief retrieve address of the program memory with the data
 *
 * @arg uint16_t id - id of the data
 *
 * @return uint8_t pointer
 *
 *****************************************************/
MY_PGM_P myPgmspace_getDataPointer(uint16_t id);

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

#endif /* PGMEM_SHARE_H */