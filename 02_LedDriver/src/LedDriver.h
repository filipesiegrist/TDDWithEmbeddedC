
#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <stdint.h>

typedef enum {
    ALL_LEDS_ON = ~0,
    ALL_LEDS_OFF = ~ALL_LEDS_ON
};

void LedDriver_Create(uint16_t* address);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
void LedDriver_TurnAllOn(void);

#endif // LEDDRIVER_H
