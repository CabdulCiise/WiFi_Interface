#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

/* Standard Includes */
#include <stdint.h>

extern uint8_t screenIndex;

void EncoderInit(void);
void PORT2_ISRHandler(void);

#endif
