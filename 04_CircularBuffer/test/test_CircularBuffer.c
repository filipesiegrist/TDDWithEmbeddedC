
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

void test_GivenEmptyBuffer_WhenQueueThenItsNotEmpty(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Simple_Float_Item = 33.3;
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Simple_Float_Item
    );
    TEST_ASSERT_FALSE(
        CircularBuffer_IsEmpty(Simple_Float_Buffer)
    );
}

void test_GivenBufferWithOneItemThenItsNotFull(void)
{
    
}

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
