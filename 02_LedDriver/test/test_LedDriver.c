
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

void test_TurnOffAnyLed(void) {
    LedDriver_TurnAllOn();
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xFF7F, virtualLeds);
}

void test_AllOn(void) {
    LedDriver_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX(0xFFFF, virtualLeds);
}

/*
 * If the driver reads the memory, writing at the buffer after
 * the creation of it will change its internal state and mess with
 * the results
 */
void test_LedMemoryIsNotReadable(void) {
    virtualLeds = 0xFFFF;
    LedDriver_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX(0x80, virtualLeds);
}

//! Similar to the one before but, at this time, check the turnOff
void test_LedMemoryIsNotReadableWhenTurningOff(void) {
    LedDriver_TurnAllOn();
    virtualLeds = 0x0000;
    LedDriver_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX(0xFF7F, virtualLeds);
}

void test_UpperAndLowerBounds(void) {
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX(0x8001, virtualLeds);
}

#endif // TEST
