
#ifdef TEST

#include "unity.h"

#include "CircularBuffer.h"


//! Helper variables
static CIRCULARBUFFER_TYPE* Simple_Float_Buffer;
static float Float_Input_Item;
static float Float_Output_Item;

static float Float_Input_Item_1;
static float Float_Input_Item_2;
static float Float_Input_Item_3;
static float Float_Input_Item_4;

static float Float_Output_Item_1;
static float Float_Output_Item_2;
static float Float_Output_Item_3;
static float Float_Output_Item_4;

//! Helper function prototypes
CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void);
CIRCULARBUFFER_TYPE* GetSingleItemBuffer(void);


void setUp(void)
{
}

void tearDown(void)
{
    Simple_Float_Buffer = NULL;
    Float_Input_Item = 0;
    Float_Output_Item = 0;

    Float_Input_Item_1 = 0;
    Float_Input_Item_2 = 0;
    Float_Input_Item_3 = 0;
    Float_Input_Item_4 = 0;

    Float_Output_Item_1 = 0;
    Float_Output_Item_2 = 0;
    Float_Output_Item_3 = 0;
    Float_Output_Item_4 = 0;
}

void test_WhenBufferIsCreated_ThenItIsEmpty(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    TEST_ASSERT_TRUE(
        CircularBuffer_IsEmpty(Simple_Float_Buffer)
    );
}

void test_WhenBufferIsCreated_ThenItIsNotFull(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    TEST_ASSERT_FALSE(
        CircularBuffer_IsFull(Simple_Float_Buffer)
    );
}

void test_WhenBufferIsCreated_ThenHasSizeZero(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    TEST_ASSERT_EQUAL(
        0,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenEmptyBufferCreated_WhenDequeue_ThenReturnFalse(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    TEST_ASSERT_FALSE(
        CircularBuffer_Dequeue(
            Simple_Float_Buffer,
            NULL
        )
    );
}

void test_GivenEmptyBufferCreated_WhenDequeue_ThenDontChangeItem(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Float_Input_Item = 67.;
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );
    
    TEST_ASSERT_EQUAL(67., Float_Input_Item);
}

void test_GivenEmptyBuffer_WhenSuccessfulQueueThenReturnTrue(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Float_Input_Item = 33.3;
    
    TEST_ASSERT_TRUE(
        CircularBuffer_Queue(
            Simple_Float_Buffer,
            (void*) &Float_Input_Item
        )
    );
}

void test_WhenSingleItemBuffer_ThenItsNotEmpty(void)
{
    Simple_Float_Buffer = GetSingleItemBuffer();
    TEST_ASSERT_FALSE(
        CircularBuffer_IsEmpty(Simple_Float_Buffer)
    );
}

void test_GivenBufferWithOneItem_ThenItsNotFull(void)
{
    Simple_Float_Buffer = GetSingleItemBuffer();
    TEST_ASSERT_FALSE(
        CircularBuffer_IsFull(Simple_Float_Buffer)
    );
}

void test_GivenBufferWithOneItem_ThenSizeIsOne(void)
{
    Simple_Float_Buffer = GetSingleItemBuffer();
    TEST_ASSERT_EQUAL_UINT16(
        1,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenEmptyBuffer_WhenItemIsInserted_ThenSameItemIsRetrieved(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Float_Input_Item = 2289;
    Float_Output_Item = 0;

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void *) &Float_Input_Item
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void *) &Float_Output_Item
    );
    TEST_ASSERT_EQUAL(
        Float_Input_Item,
        Float_Output_Item
    );
}

void test_GivenSingleItemBuffer_WhenDequeue_ThenReturnTrue(void)
{
    Simple_Float_Buffer = GetSingleItemBuffer();
    TEST_ASSERT_TRUE(
        CircularBuffer_Dequeue(
            Simple_Float_Buffer,
            (void*) &Float_Output_Item
        )
    );
}

void test_GivenSingleItemBuffer_WhenDequeue_ThenItIsEmpty(void)
{
    Simple_Float_Buffer = GetSingleItemBuffer();
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );

    TEST_ASSERT_TRUE(
        CircularBuffer_IsEmpty(Simple_Float_Buffer)
    );
}

void test_GivenSingleItemBuffer_WhenDequeue_ThenSizeIsZero(void)
{
    Simple_Float_Buffer = GetSingleItemBuffer();
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );

    TEST_ASSERT_EQUAL_UINT16(
        0,
        CircularBuffer_GetSize(
            Simple_Float_Buffer
        )
    );

}

void test_GivenEmptyBuffer_WhenZeroIsQueued_ThenZeroIsDequeued(void)
{
    Float_Input_Item = 0;
    Float_Output_Item = 0.112;
    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );
    TEST_ASSERT_EQUAL(
        Float_Input_Item,
        Float_Output_Item
    );
}

void test_GivenTwoItemsQueued_WhenDequeued_ThenValuesAreReturnedInFifoOrder(void)
{
    Float_Input_Item_1 = 1.5f;
    Float_Input_Item_2 = 2.7f;
    Float_Output_Item_1 = 0.0f;
    Float_Output_Item_2 = 0.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_1
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_2
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item_1
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item_2
    );

    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_1, Float_Output_Item_1);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_2, Float_Output_Item_2);
}

void test_GivenThreeItemsQueued_WhenGetSizeIsCalled_ThenReturnThree(void)
{
    Float_Input_Item_1 = 1.0f;
    Float_Input_Item_2 = 2.0f;
    Float_Input_Item_3 = 3.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_2
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_3
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_1
    );

    TEST_ASSERT_EQUAL_UINT16(
        3,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenFourItemsQueuedAndTwoDequeued_WhenGetSizeIsCalled_ThenReturnTwo(void)
{
    Float_Input_Item = 1.0f;
    Float_Output_Item = 0.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );

    TEST_ASSERT_EQUAL_UINT16(
        2,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenThreeItemsQueued_WhenDequeued_ThenValuesAreReturnedInFifoOrder(void)
{
    Float_Input_Item_1 = 1.5f;
    Float_Input_Item_2 = 2.7f;
    Float_Input_Item_3 = 3.14f;

    Float_Output_Item_1 = 0.0f;
    Float_Output_Item_2 = 0.0f;
    Float_Output_Item_3 = 0.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*)&Float_Input_Item_1);
    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*)&Float_Input_Item_2);
    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*)&Float_Input_Item_3);

    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*)&Float_Output_Item_1);
    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*)&Float_Output_Item_2);
    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*)&Float_Output_Item_3);

    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_1, Float_Output_Item_1);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_2, Float_Output_Item_2);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_3, Float_Output_Item_3);
}

void test_GivenInterleavedQueuesAndDequeues_ThenValuesAreReturnedInFifoOrder(void)
{
    Float_Input_Item_1 = 1.0f;
    Float_Input_Item_2 = 2.0f;
    Float_Input_Item_3 = 3.0f;
    Float_Input_Item_4 = 4.0f;
    Float_Output_Item_1 = 0.0f;
    Float_Output_Item_2 = 0.0f;
    Float_Output_Item_3 = 0.0f;
    Float_Output_Item_4 = 0.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_1
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_2
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item_1
    );

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_3
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item_4
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item_2
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item_3
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item_4
    );

    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_1, Float_Output_Item_1);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_2, Float_Output_Item_2);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_3, Float_Output_Item_3);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_4, Float_Output_Item_4);
}

// void test_(void)
// {
//     
// }

// void test_(void)
// {
//     
// }

// void test_(void)
// {
//     
// }

// void test_(void)
// {
//     
// }

// void test_(void)
// {
//     
// }

//! Helper functions

CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void) {
    CIRCULARBUFFER_TYPE* buf;
    buf = CircularBuffer_Create(sizeof(float));
    return buf;
}

CIRCULARBUFFER_TYPE* GetSingleItemBuffer(void) {
    CIRCULARBUFFER_TYPE* buf;
    float input_item;

    buf = GetSimpleEmptyBuffer();
    input_item = 33.3;
    (void) CircularBuffer_Queue(
        buf,
        (void*) &input_item
    );
    return buf;
}

#endif // TEST
