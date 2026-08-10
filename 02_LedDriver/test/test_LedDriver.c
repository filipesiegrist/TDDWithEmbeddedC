
#ifdef TEST

#include "unity.h"

#include "LedDriver.h"
#include "RuntimeErrorStub.h"

static uint16_t virtualLeds;

void setUp(void)
{
    LedDriver_Create(&virtualLeds);
    RuntimeErrorStub_Reset();
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

void test_OutOfBoundsTurnOnDoesNoHarm(void) {
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(3141);
    TEST_ASSERT_EQUAL_HEX(0, virtualLeds);
}

//! Same as before, but for turn OFF
void test_OutOfBoundsTurnOffDoesNoHarm(void) {
    LedDriver_TurnAllOn();

    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(3141);
    TEST_ASSERT_EQUAL_HEX(0xFFFF, virtualLeds);
}

void test_OutOfBoundsTurnOnProducesRuntimeError(void) {
    LedDriver_TurnOn(-1);
    TEST_ASSERT_EQUAL_STRING(
        "LED Driver: out-of-bounds LED",
        RuntimeErrorStub_GetLastError()
    );
    TEST_ASSERT_EQUAL(
        -1,
        RuntimeErrorStub_GetLastParameter()
    );
}

void test_OutOfBoundsTurnOffProducesRuntimeError(void) {
    LedDriver_TurnOff(17);
    TEST_ASSERT_EQUAL_STRING(
        "LED Driver: out-of-bounds LED",
        RuntimeErrorStub_GetLastError()
    );
    TEST_ASSERT_EQUAL(
        17,
        RuntimeErrorStub_GetLastParameter()
    );
}

void test_IsOn(void) {
    TEST_ASSERT_FALSE(LedDriver_IsOn(11));
    LedDriver_TurnOn(11);
    TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}

void test_OutOfBoundsLedsAreAlwaysOff(void) {
    TEST_ASSERT_FALSE(LedDriver_IsOn(FIRST_LED - 1));
    TEST_ASSERT_FALSE(LedDriver_IsOn(LAST_LED + 1));
}


#endif // TEST
