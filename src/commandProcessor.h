/**************************************************************
 * Arduino Bencher
 *
 * @file commandProcessor.h
 *
 * @brief container to manipulate the storage of commands
 *************************************************************/

#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <stdbool.h>
#include "FreeRTOS.h"

/******************************************************
 * @name commandProcessor_Init
 *
 * @brief append char to current command
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
void commandProcessor_Init(void);

/******************************************************
 * @name commandProcessor_append
 *
 * @brief append char to current command
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
uint8_t commandProcessor_append(char c);

/******************************************************
 * @name commandProcessor_remove
 *
 * @brief delete
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
uint8_t commandProcessor_remove(void);

/******************************************************
 * @name commandProcessor_clear
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
void commandProcessor_clear(void);

/******************************************************
 * @name commandProcessor_parse
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
uint8_t commandProcessor_parse(void);

/******************************************************
 * @name commandProcessor_commandRun
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
eResult commandProcessor_commandRun(void);

#endif /* COMMANDPROCESSOR_H */