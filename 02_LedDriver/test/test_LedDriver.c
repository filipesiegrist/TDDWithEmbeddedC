
#ifdef TEST

#include "unity.h"

#include "LedDriver.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LEDsOffAfterCreate(void) {
    uint16_t virtualLeds;

    virtualLeds = 0xFFFF;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_TurnOnOneLED(void) {
    uint16_t virtualLeds;
    
    LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

void test_TurnOffOneLed(void) {
    uint16_t virtualLeds;
    
    LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

#endif // TEST
