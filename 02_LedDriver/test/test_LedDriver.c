
#ifdef TEST

#include "unity.h"

#include "LedDriver.h"

static uint16_t virtualLeds;

void setUp(void)
{
    LedDriver_Create(&virtualLeds);
}

void tearDown(void)
{
}

void test_LedsOffAfterCreate(void) {
    virtualLeds = 0xFFFF;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_TurnOnOneLed(void) {
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

void test_TurnOffOneLed(void) {
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_TurnOnMultipleLeds(void) {
    LedDriver_TurnOn(9);
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

// void test_TurnOffAnyLed(void) {
//     LedDriver_TurnOn(9);
//     LedDriver_TurnOn(8);
//     LedDriver_TurnOff(8);
//     TEST_ASSERT_EQUAL_HEX16(0x100, virtualLeds);
// }

void test_AllOn(void) {
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX(0xFFFF, virtualLeds);
}

#endif // TEST
