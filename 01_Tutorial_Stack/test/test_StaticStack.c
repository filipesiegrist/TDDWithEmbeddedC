
#ifdef TEST

#include "unity.h"

#include "StaticStack.h"

STATICSTACK_TYPE stack;

void setUp(void)
{
    stack = StaticStack__Initialize();
}

void tearDown(void)
{
}

void test_WhenStackIsInitialized__ItShouldBeEmpty(void)
{
    TEST_ASSERT_TRUE(StaticStack__IsEmpty(stack));
}

void test_StackShouldAcceptGenericValues(void)
{
    GENERIC_TYPE value = 10;
    StaticStack__Push(&stack, value);
}

void test_WhenItemIsPushed_ThenStackIsNotEmpty(void)
{
    GENERIC_TYPE value = 10;
    StaticStack__Push(&stack, value);
    TEST_ASSERT_FALSE(StaticStack__IsEmpty(stack));
}

void test_WhenZeroItemIsPushed_ThenStackIsNotEmpty(void)
{
    GENERIC_TYPE value = 0;
    StaticStack__Push(&stack, value);
    TEST_ASSERT_FALSE(StaticStack__IsEmpty(stack));
}

void test_WhenEmptyStackIsPopped_ThenReturnInvalidValue(void)
{
    TEST_ASSERT_EQUAL(GENERIC_TYPE_ERROR, StaticStack__Pop(&stack));
}

void test_PopSameItemThatWasPushed(void)
{
    GENERIC_TYPE value = 6;
    StaticStack__Push(&stack, value);
    TEST_ASSERT_EQUAL(value, StaticStack__Pop(&stack));
}

void test_WhenPushAndPop_StackShouldBeEmpty(void)
{
    GENERIC_TYPE value = 123;
    StaticStack__Push(&stack, value);
    (void) StaticStack__Pop(&stack);
    TEST_ASSERT_TRUE(StaticStack__IsEmpty(stack));
}

void test_When2ItemsArePushedandPopped_RetrieveThenInLIFOLogic(void)
{
    GENERIC_TYPE value_1 = 67;
    GENERIC_TYPE value_2 = 60000;
    StaticStack__Push(&stack, value_1);
    StaticStack__Push(&stack, value_2);
    TEST_ASSERT_EQUAL(value_2, StaticStack__Pop(&stack));
    TEST_ASSERT_EQUAL(value_1, StaticStack__Pop(&stack));
}

void test_When2ItemsArePushedAnd1IsPopped_ShouldNotBeEmpty(void)
{
    GENERIC_TYPE value_1 = 255;
    GENERIC_TYPE value_2 = 3600;
    
    StaticStack__Push(&stack, value_1);
    StaticStack__Push(&stack, value_2);

    (void) StaticStack__Pop(&stack);
    
    TEST_ASSERT_FALSE(StaticStack__IsEmpty(stack));
}

void test_When2ItemsArePushedAndPopped_ShouldBeEmpty(void)
{
    GENERIC_TYPE value = 3;
    
    StaticStack__Push(&stack, value);
    StaticStack__Push(&stack, value);
    (void) StaticStack__Pop(&stack);
    (void) StaticStack__Pop(&stack);
    
    TEST_ASSERT_TRUE(StaticStack__IsEmpty(stack));
}

void test_When3ItemsArePushedAnd4ArePopped_ReturnThoseWithTheLastBeingInvalid(void)
{
    GENERIC_TYPE value_1 = 37123;
    GENERIC_TYPE value_2 = 1440;
    GENERIC_TYPE value_3 = 7777;

    StaticStack__Push(&stack, value_1);
    StaticStack__Push(&stack, value_2);
    StaticStack__Push(&stack, value_3);

    TEST_ASSERT_EQUAL(value_3, StaticStack__Pop(&stack));
    TEST_ASSERT_EQUAL(value_2, StaticStack__Pop(&stack));
    TEST_ASSERT_EQUAL(value_1, StaticStack__Pop(&stack));
    TEST_ASSERT_EQUAL(GENERIC_TYPE_ERROR, StaticStack__Pop(&stack));
}

void test_WhenStackIsFilled_AllItemsCanBeSafelyRetrieved(void)
{
    GENERIC_TYPE value = 1022;
    uint16_t i = 0;

    for (i = 0; i < STATICSTACK_SIZE; i++) {
        StaticStack__Push(&stack, value);
        value++;
    }
    
    for (; i > 0; i--) {
        value--;
        TEST_ASSERT_EQUAL(value, StaticStack__Pop(&stack));
    }
}

void test_GivenStackIsFull_WhenAnExtraItemIsPushed_ThenDontOverflowIt(void)
{
    GENERIC_TYPE value = 8066;
    uint16_t i = 0;

    for (i = 0; i < STATICSTACK_SIZE; i++) {
        StaticStack__Push(&stack, value);
        value++;
    }
    StaticStack__Push(&stack, value);
    
    value--;
    TEST_ASSERT_EQUAL(value, StaticStack__Pop(&stack));
}

void test_WhenGenericTypeErrorValueIsPushed_ThenPopReturnsTheSameValue(void)
{
    GENERIC_TYPE value = GENERIC_TYPE_ERROR;
    StaticStack__Push(&stack, value);
    TEST_ASSERT_FALSE(StaticStack__IsEmpty(stack));
    
    TEST_ASSERT_EQUAL(GENERIC_TYPE_ERROR, StaticStack__Pop(&stack));
    TEST_ASSERT_TRUE(StaticStack__IsEmpty(stack));
}


#endif // TEST
