/**************************************************************
 * Arduino Bencher
 *
 * @file channelInterface.h
 *
 * @brief container with functions related to the control of
 * the GPIO ports (and relays connected)
 *************************************************************/

#ifndef CHANNELINTERFACE_H
#define CHANNELINTERFACE_H

#include "appTypes.h"

void channelInterface_task(void *pvParameters);

uint8_t channelInterface_getLedState(void);

#endif /* CHANNELINTERFACE_H */