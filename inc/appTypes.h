
/**************************************************************
 * Arduino Bencher
 *
 * @file appTypes.h
 *
 * @brief header with types/definitions used in the whole project
 *************************************************************/

#ifndef APPTYPES_H
#define APPTYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum{
    eResult_OK,
    eResult_NOT_OK,
    eResult_PENDING
} eResult;

#define DIO_ACTION_WRITE 1
#define DIO_ACTION_READ 2
#define DIO_LEVEL_LOW 0
#define DIO_LEVEL_HIGH 1
#define DIO_LEVEL_INVALID 3

typedef struct{
    uint8_t action;
    uint8_t gpioId;
    uint8_t level;
} dioMsgType;

typedef struct{
    uint32_t taskPeriod; 
} taskParams;

#endif /* APPTYPES_H */