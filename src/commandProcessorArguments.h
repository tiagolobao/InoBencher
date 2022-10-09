
/**************************************************************
 * Arduino Bencher
 *
 * @file commandProcessorArguments.h
 *
 * @brief functions to read the input arguments (included in cmdActions)
 *************************************************************/

#ifndef COMMANDPROCESSOR_ARGS_H
#define COMMANDPROCESSOR_ARGS_H

/******************************************************
 * @name commandProcessor_getArg_d
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
eResult commandProcessor_getArg_d(const uint8_t p, int *d);

/******************************************************
 * @name commandProcessor_getArg_d
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
eResult commandProcessor_getArg_s(const uint8_t p, char *s, const uint8_t len);

/******************************************************
 * @name commandProcessor_getArg_d
 *
 * @brief initializes the Serial communication
 *
 * @arg uint32_t baud - baud rate (9600u..115200u)
 *      uint8_t high_speed (1 means high speed)
 *
 * @return void
 *
 *****************************************************/
eResult commandProcessor_compArg_s(const uint8_t p, const char *s);

#endif /* COMMANDPROCESSOR_ARGS_H */