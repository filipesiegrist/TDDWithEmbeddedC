
#ifdef TEST

#include "unity.h"

#include "CircularBuffer.h"


//! Helper variables
static CIRCULARBUFFER_TYPE* Simple_Float_Buffer;
static float Simple_Float_Item;

//! Helper function prototypes
CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void);
CIRCULARBUFFER_TYPE* GetSingleItemBuffer(void);


void setUp(void)
{
}

void tearDown(void)
{
    Simple_Float_Buffer = NULL;
    Simple_Float_Item = 0;
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
    Simple_Float_Item = 67.;
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Simple_Float_Item
    );
    
    TEST_ASSERT_EQUAL(67., Simple_Float_Item);
}

void test_GivenEmptyBuffer_WhenSuccessfulQueueThenReturnTrue(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Simple_Float_Item = 33.3;
    
    TEST_ASSERT_TRUE(
        CircularBuffer_Queue(
            Simple_Float_Buffer,
            (void*) &Simple_Float_Item
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
    float out_float_item;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Simple_Float_Item = 2289;
    out_float_item = 0;

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void *) &Simple_Float_Item
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void *) &out_float_item
    );
    TEST_ASSERT_EQUAL(
        Simple_Float_Item,
        out_float_item
    );
}

void test_GivenSingleItemBuffer_WhenDequeue_ThenReturnTrue(void)
{
    float out_item;

    Simple_Float_Buffer = GetSingleItemBuffer();
    TEST_ASSERT_TRUE(
        CircularBuffer_Dequeue(
            Simple_Float_Buffer,
            (void*) &out_item
        )
    );
}

void test_GivenSingleItemBuffer_WhenDequeue_ThenItIsEmpty(void)
{
    float out_item;

    Simple_Float_Buffer = GetSingleItemBuffer();
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &out_item
    );

    TEST_ASSERT_TRUE(
        CircularBuffer_IsEmpty(Simple_Float_Buffer)
    );
}

void test_GivenSingleItemBuffer_WhenDequeue_ThenSizeIsZero(void)
{
    float out_item;

    Simple_Float_Buffer = GetSingleItemBuffer();
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &out_item
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
    float in_item;
    float out_item;

    in_item = 0;
    out_item = 0.112;
    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &in_item
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &out_item
    );
    TEST_ASSERT_EQUAL(
        in_item,
        out_item
    );
}

void test_GivenTwoItemsQueued_WhenDequeued_ThenValuesAreReturnedInFifoOrder(void)
{
    float first_in;
    float second_in;
    float first_out;
    float second_out;

    first_in = 1.5f;
    second_in = 2.7f;
    first_out = 0.0f;
    second_out = 0.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &first_in
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &second_in
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &first_out
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &second_out
    );

    TEST_ASSERT_EQUAL_FLOAT(first_in, first_out);
    TEST_ASSERT_EQUAL_FLOAT(second_in, second_out);
}

void test_GivenThreeItemsQueued_WhenGetSizeIsCalled_ThenReturnThree(void)
{
    float item1 = 1.0f;
    float item2 = 2.0f;
    float item3 = 3.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item2
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item3
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item1
    );

    TEST_ASSERT_EQUAL_UINT16(
        3,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenFourItemsQueuedAndTwoDequeued_WhenGetSizeIsCalled_ThenReturnTwo(void)
{
    float item = 1.0f;
    float out_item = 0.0f;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &item
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &out_item
    );
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &out_item
    );

    TEST_ASSERT_EQUAL_UINT16(
        2,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
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
    float item;

    buf = GetSimpleEmptyBuffer();
    item = 33.3;
    (void) CircularBuffer_Queue(
        buf,
        (void*) &item
    );
    return buf;
}

#endif // TEST
