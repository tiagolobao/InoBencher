
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

typedef enum{
    eResult_OK,
    eResult_NOT_OK,
    eResult_PENDING
} eResult;

typedef struct{
    uint32_t taskPeriod; 
} taskParams;

#endif /* APPTYPES_H */