#include "LedDriver.h"
#include "RuntimeError.h"

static uint16_t* ledsAddress;
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit(int ledNumber);
static void updateHardware(void);
static bool isLedOutOfBounds(int ledNumber);
static void setLedImageBit(int ledNumber);
static void clearLedImageBit(int ledNumber);

// =============== Public methods =================

void LedDriver_Create(uint16_t* address) {
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_TurnOn(int ledNumber) {
    if (isLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return;
    }
    
    setLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber) {
    if (isLedOutOfBounds(ledNumber)) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return;
    }
    
    clearLedImageBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnAllOn(void) {
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

bool LedDriver_IsOn(int ledNumber) {
    return (ledsImage & convertLedNumberToBit(ledNumber));
}

// =============== Private methods =================

static uint16_t convertLedNumberToBit(int ledNumber) {
    return (1 << (ledNumber - 1));
}

static void updateHardware(void) {
    *ledsAddress = ledsImage;
}

static bool isLedOutOfBounds(int ledNumber) {
    return (ledNumber < FIRST_LED || ledNumber > LAST_LED);
}

static void setLedImageBit(int ledNumber) {
    ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber) {
    ledsImage &= ~convertLedNumberToBit(ledNumber);
}
