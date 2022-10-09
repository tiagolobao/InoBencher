
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
 * @brief get argument in form of a decimal number
 *
 * @arg uint8_t p - position of the argument
 *      int* output 
 *
 * @return eResult - if the argument was properly written
 *
 *****************************************************/
eResult commandProcessor_getArg_d(const uint8_t p, int *d);

/******************************************************
 * @name commandProcessor_getArg_d
 *
 * @brief get argument in form of a string
 *
 * @arg uint8_t p - position of the argument
 *      char* s - string output
 *      uint8_t len - max lenght of the output string
 *
 * @return eResult - if the argument was properly written
 *
 *****************************************************/
eResult commandProcessor_getArg_s(const uint8_t p, char *s, const uint8_t len);

/******************************************************
 * @name commandProcessor_getArg_d
 *
 * @brief compares argument with a predefined string
 *
 * @arg uint8_t p - position of the argument
 *      char* s - string to be compared
 *
 * @return eResult - if the argument matches the string it will return eResult_OK
 * it will return eResult_NOT_OK otherwise
 *
 *****************************************************/
eResult commandProcessor_compArg_s(const uint8_t p, const char *s);

#endif /* COMMANDPROCESSOR_ARGS_H */