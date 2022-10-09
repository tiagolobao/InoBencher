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
 * @brief initialize variables inside command processor
 *
 * @arg void
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
 * @arg char c - character to be appended
 *
 * @return boolean in uint8_t type to declare if operation was ok
 *
 *****************************************************/
uint8_t commandProcessor_append(char c);

/******************************************************
 * @name commandProcessor_remove
 *
 * @brief delete char from current command
 *
 * @arg void
 *
 * @return boolean in uint8_t type to declare if operation was ok
 *
 *****************************************************/
uint8_t commandProcessor_remove(void);

/******************************************************
 * @name commandProcessor_clear
 *
 * @brief clear all variables related to the incomming command
 *
 * @arg void
 *
 * @return void
 *
 *****************************************************/
void commandProcessor_clear(void);

/******************************************************
 * @name commandProcessor_parse
 *
 * @brief parses the written command
 *
 * @arg void
 *
 * @return eResult telling if the command was properly written
 *
 *****************************************************/
eResult commandProcessor_parse(void);

/******************************************************
 * @name commandProcessor_commandRun
 *
 * @brief runs the command. (parse should be called first)
 *
 * @arg void
 *
 * @return eResult 
 *  PENDING - this function should be called again in order to finish the command
 *  OK or NOK - command finished
 *
 *****************************************************/
eResult commandProcessor_commandRun(void);

#endif /* COMMANDPROCESSOR_H */