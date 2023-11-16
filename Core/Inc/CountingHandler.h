/*
 * CountingHandler.h
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */


#ifndef COUNTINGHANDLER_H_
#define COUNTINGHANDLER_H_

#include <stdint.h>
#include <stdbool.h>
#include "SendData.h"

void CountingHandler_init(uint16_t *pulseCount, bool *flagPulso);

void CountingHandler(uint16_t *pulseCount);


#endif
