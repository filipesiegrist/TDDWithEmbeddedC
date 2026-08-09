#include "LedDriver.h"

static uint16_t* ledsAddress;

static uint16_t convertLedNumberToBit(int ledNumber);

void LedDriver_Create(uint16_t* address) {
    ledsAddress = address;
    *ledsAddress = ALL_LEDS_OFF;
}

void LedDriver_TurnOn(int ledNumber) {
    *ledsAddress |= convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOff(int ledNumber) {
    *ledsAddress = 0;
}

void LedDriver_TurnAllOn(void) {
    *ledsAddress = ALL_LEDS_ON;
}



static uint16_t convertLedNumberToBit(int ledNumber) {
    return (1 << (ledNumber - 1));
}
