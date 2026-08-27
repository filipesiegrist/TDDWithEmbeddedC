
#ifdef TEST

#include "unity.h"

#include "DynamicStack.h"

//! Helper functions
static DYNAMICSTACK_TYPE* GetASimpleStack(void);
static DYNAMICSTACK_TYPE* GetOneItemStack(int value);
static DYNAMICSTACK_TYPE* GetStackWith2Ints(int first_value, int second_value);
static DYNAMICSTACK_TYPE* GetCustomStackWithOneItem(void);
static DYNAMICSTACK_TYPE* GetStackWithNInts(int count);
static DYNAMICSTACK_TYPE* GetCustomStackWithNItems(int count);

//! Helper variables and Types

typedef struct {
    uint32_t sensor_id;
    float temperature;
    bool is_active;
} EXOTIC_STRUCT_TYPE;

typedef struct {
    int huge_array[50];
    bool some_flag;
    double some_value;
} HUGE_STRUCT_TYPE;

static DYNAMICSTACK_TYPE* Example_Stack;
static int Popped_Item;
static int Pushed_Item;


static HUGE_STRUCT_TYPE Huge_Pushed_Struct = {
    .huge_array = {55},
    .some_flag = true,
    .some_value = 3.141592
};
static HUGE_STRUCT_TYPE Huge_Popped_Struct = {0};


void setUp(void)
{
    Example_Stack = NULL;
    Popped_Item = 0;
    Pushed_Item = 0;
}

void tearDown(void)
{
    // DynamicStack__Clear(Example_Stack);
}

void test_WhenNoStackFound_ThenReturnEmpty(void)
{
    TEST_ASSERT_TRUE(DynamicStack__IsEmpty(NULL));
}

void test_GivenStackWasJustCreated_ThenReturnEmpty(void)
{
    Example_Stack = GetASimpleStack();
    TEST_ASSERT_TRUE(DynamicStack__IsEmpty(Example_Stack));
}

void test_WhenNoStackFound_ThenReturnSize0(void)
{
    TEST_ASSERT_EQUAL(0, DynamicStack__GetSize(NULL));
}

void test_GivenStackWasJustCreated_ThenReturnSize0(void)
{
    Example_Stack = GetASimpleStack();
    TEST_ASSERT_EQUAL(0, DynamicStack__GetSize(Example_Stack));
}

void test_WhenStackHasOneItem_ItShouldNotBeEmpty(void)
{
    Example_Stack = GetASimpleStack();
    Pushed_Item = 4;

    (void) DynamicStack__Push(Example_Stack, &Pushed_Item);
    TEST_ASSERT_FALSE(DynamicStack__IsEmpty(Example_Stack));
}

void test_WhenStackHasOneItem_ThenItsSizeEqualsOne(void)
{
    Example_Stack = GetOneItemStack(10);
    TEST_ASSERT_EQUAL(1, DynamicStack__GetSize(Example_Stack));
}

void test_GivenEmptyStack_PoppingShouldReturnFalse(void)
{
    Example_Stack = GetASimpleStack();

    TEST_ASSERT_FALSE(DynamicStack__Pop(Example_Stack, &Popped_Item));
}

void test_GivenStackWithOneItem_WhenPopItem_ThenReturnTrue(void)
{
    Example_Stack = GetOneItemStack(655);
    TEST_ASSERT_TRUE(DynamicStack__Pop(Example_Stack, &Popped_Item));
}

void test_GivenStackWithOneItem_WhenPop_ThenReturnTheSameValue(void)
{
    const int PUSHED_VALUE = 67;
    
    Example_Stack = GetOneItemStack(PUSHED_VALUE);
    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    TEST_ASSERT_EQUAL(PUSHED_VALUE, Popped_Item);
}

void test_GivenStackWithOneItem_WhenPop_ThenStackIsEmpty(void)
{
    Example_Stack = GetOneItemStack(0);
    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    TEST_ASSERT_TRUE(DynamicStack__IsEmpty(Example_Stack));
}

void test_GivenStackWithOneItem_WhenPop_ThenStackSizeIsZero(void)
{   
    Example_Stack = GetOneItemStack(0);
    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    TEST_ASSERT_EQUAL(0, DynamicStack__GetSize(Example_Stack));
}

void test_Given2ItemsArePushed_WhenPop_ThenStackIsNotEmpty(void)
{
    Example_Stack = GetStackWith2Ints(1, 2);

    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    TEST_ASSERT_FALSE(DynamicStack__IsEmpty(Example_Stack));
}

void test_Given2ItemsArePushed_WhenPop_ThenLastItemIsReturned(void)
{
    Example_Stack = GetStackWith2Ints(2887, -15);

    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    TEST_ASSERT_EQUAL(-15, Popped_Item);
}

void test_GivenEmptyStack_WhenPop_ThenValueRemainsUnchanged(void)
{
    Example_Stack = GetASimpleStack();
    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    TEST_ASSERT_EQUAL(0, Popped_Item);
}

void test_Given2ItemsArePushedAndOneAlreadyPopped_WhenPop_ThenFirstItemIsReturned(void)
{
    Example_Stack = GetStackWith2Ints(0, 14);
    
    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    (void) DynamicStack__Pop(Example_Stack, &Popped_Item);
    
    TEST_ASSERT_EQUAL(0, Popped_Item);
}

void test_PushNormalValueToTheStackShouldReturnTrue(void)
{
    Pushed_Item = 555;
    Example_Stack = GetASimpleStack();
    TEST_ASSERT_TRUE(DynamicStack__Push(Example_Stack, &Pushed_Item));
}

void test_WhenPushToAnInvalidStack_ThenReturnFalse(void)
{
    Pushed_Item = 1;
    TEST_ASSERT_FALSE(DynamicStack__Push(NULL, &Pushed_Item));
}

void test_WhenPushInvalidValue_ThenReturnFalse(void)
{
    Example_Stack = GetASimpleStack();

    TEST_ASSERT_FALSE(DynamicStack__Push(Example_Stack, NULL));
}

void test_WhenStackWith4Items_ThenSizeIs4(void)
{
    Example_Stack = GetASimpleStack();
    Pushed_Item = 0;
    
    (void) DynamicStack__Push(Example_Stack, &Pushed_Item);
    (void) DynamicStack__Push(Example_Stack, &Pushed_Item);
    (void) DynamicStack__Push(Example_Stack, &Pushed_Item);
    (void) DynamicStack__Push(Example_Stack, &Pushed_Item);
    
    TEST_ASSERT_EQUAL(4, DynamicStack__GetSize(Example_Stack));
}

void test_TwoStacksDontInterfereWithEachOther(void)
{
    DYNAMICSTACK_TYPE* another_stack;
    
    Example_Stack = GetOneItemStack(6);
    another_stack = GetASimpleStack();

    TEST_ASSERT_FALSE(DynamicStack__IsEmpty(Example_Stack));
    TEST_ASSERT_TRUE(DynamicStack__IsEmpty(another_stack));
}

void test_GivenInvalidStack_WhenPop_ThenReturnFalse(void) {
    TEST_ASSERT_FALSE(DynamicStack__Pop(NULL, &Popped_Item));
}

void test_GivenInvalidStack_WhenPop_ThenDontChangeTheValue(void) {
    Popped_Item = 45;
    (void) DynamicStack__Pop(NULL, &Popped_Item);
    TEST_ASSERT_EQUAL(45, Popped_Item);
}

void test_WhenCustomStructItemPushed_ThenThisItemIsRetrieved(void)
{
    EXOTIC_STRUCT_TYPE my_struct = { .sensor_id = 1045, .temperature = 25.5f, .is_active = true };
    EXOTIC_STRUCT_TYPE popped_struct = {0};
    
    DYNAMICSTACK_TYPE* custom_stack = DynamicStack__Initialize(sizeof(EXOTIC_STRUCT_TYPE));

    DynamicStack__Push(custom_stack, &my_struct);
    DynamicStack__Pop(custom_stack, &popped_struct);
    
    TEST_ASSERT_EQUAL_MEMORY(&my_struct, &popped_struct, sizeof(EXOTIC_STRUCT_TYPE));
}

void test_GivenHugeStructPushed_WhenPop_ThenItIsReturned(void)
{
    DYNAMICSTACK_TYPE* custom_stack;

    custom_stack = GetCustomStackWithOneItem();

    DynamicStack__Pop(custom_stack, &Huge_Popped_Struct);
    
    TEST_ASSERT_EQUAL_MEMORY(
        &Huge_Pushed_Struct,
        &Huge_Popped_Struct,
        sizeof(HUGE_STRUCT_TYPE)
    );
}

void test_GivenInvalidStack_ClearShouldDoNothing(void)
{
    DynamicStack__Clear(NULL);
}

void test_GivenValidStack_WhenCleared_PointToNull(void)
{
    Example_Stack = GetOneItemStack(67);
    DynamicStack__Clear(&Example_Stack);
    TEST_ASSERT_EQUAL(NULL, Example_Stack);
}

void test_WhenCustomStructPushed_ThenStackShouldHaveSizeOne(void)
{
    DYNAMICSTACK_TYPE* custom_stack;

    custom_stack = GetCustomStackWithOneItem();
    TEST_ASSERT_EQUAL(1, DynamicStack__GetSize(custom_stack));
}

void test_GivenEmptyStack_WhenPush4Items_ThenSizeIs4(void)
{
    Example_Stack = GetStackWithNInts(4);
    TEST_ASSERT_EQUAL(4, DynamicStack__GetSize(Example_Stack));
}

void test_GivenEmptyStack_WhenPush4Items_ThenStackIsNotEmpty(void)
{
    Example_Stack = GetStackWithNInts(4);
    TEST_ASSERT_FALSE(DynamicStack__IsEmpty(Example_Stack));
}

void test_GivenEmptyStack_WhenPush10Ints_ThenSizeIs10(void)
{
    Example_Stack = GetStackWithNInts(10);
    TEST_ASSERT_EQUAL(10, DynamicStack__GetSize(Example_Stack));
}

void test_GivenEmptyStack_WhenPush10CustomStructs_ThenSizeIs10(void)
{
    DYNAMICSTACK_TYPE* custom_stack;
    
    custom_stack = GetCustomStackWithNItems(10);
    TEST_ASSERT_EQUAL(10, DynamicStack__GetSize(custom_stack));
}

void test_GivenValidItem_WhenPush_ThenOriginalValueRemainsUnchanged(void)
{
    const int ORIGINAL_VALUE = 9876;
    int item_to_push = ORIGINAL_VALUE;
    
    Example_Stack = GetASimpleStack();
    (void) DynamicStack__Push(Example_Stack, &item_to_push);
    
    TEST_ASSERT_EQUAL(ORIGINAL_VALUE, item_to_push);
}

void test_GivenTwoDifferentStacks_WhenPushingAndPopping_ThenTheyDoNotInterfere(void)
{
    DYNAMICSTACK_TYPE* int_stack;
    DYNAMICSTACK_TYPE* custom_stack;
    
    int popped_int = 0;
    int pushed_int = 100;
    HUGE_STRUCT_TYPE popped_struct = {0};

    int_stack = GetASimpleStack();
    custom_stack = GetCustomStackWithOneItem(); 

    (void) DynamicStack__Push(int_stack, &pushed_int);
    
    (void) DynamicStack__Pop(int_stack, &popped_int);
    (void) DynamicStack__Pop(custom_stack, &popped_struct);

    TEST_ASSERT_EQUAL(100, popped_int);
    TEST_ASSERT_EQUAL_MEMORY(&Huge_Pushed_Struct, &popped_struct, sizeof(HUGE_STRUCT_TYPE));
}


//! Helper Functions 

static DYNAMICSTACK_TYPE* GetASimpleStack(void)
{
    DYNAMICSTACK_TYPE* stack;
    
    stack = DynamicStack__Initialize(sizeof(int));
    return stack;
}

static DYNAMICSTACK_TYPE* GetOneItemStack(int value)
{
    int push_value;
    DYNAMICSTACK_TYPE* stack;
    
    stack = GetASimpleStack();
    push_value = value;
    (void) DynamicStack__Push(stack, &push_value);
    return stack;
}

static DYNAMICSTACK_TYPE* GetStackWith2Ints(int first_value, int second_value)
{
    DYNAMICSTACK_TYPE* stack;
    
    stack = DynamicStack__Initialize(sizeof(int));
    DynamicStack__Push(stack, &first_value);
    DynamicStack__Push(stack, &second_value);
    return stack;
}

static DYNAMICSTACK_TYPE* GetCustomStackWithOneItem(void) {
    DYNAMICSTACK_TYPE* stack;

    stack = DynamicStack__Initialize(sizeof(HUGE_STRUCT_TYPE));
    (void) DynamicStack__Push(stack, &Huge_Pushed_Struct);


    return stack;
}

static DYNAMICSTACK_TYPE* GetStackWithNInts(int count) 
{
    DYNAMICSTACK_TYPE* stack;
    int dummy_value = 42;
    
    stack = DynamicStack__Initialize(sizeof(int));
    for (int i = 0; i < count; i++) {
        (void) DynamicStack__Push(stack, &dummy_value);
    }
    return stack;
}

static DYNAMICSTACK_TYPE* GetCustomStackWithNItems(int count) 
{
    DYNAMICSTACK_TYPE* stack;
    
    stack = DynamicStack__Initialize(sizeof(HUGE_STRUCT_TYPE));
    for (int i = 0; i < count; i++) {
        (void) DynamicStack__Push(stack, &Huge_Pushed_Struct);
    }
    return stack;
}

#endif // TEST
