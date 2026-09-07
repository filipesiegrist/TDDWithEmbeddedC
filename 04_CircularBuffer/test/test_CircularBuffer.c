
#ifdef TEST

#include "unity.h"

#include "CircularBuffer.h"


//! Helper variables
static CIRCULARBUFFER_TYPE* Simple_Float_Buffer;

//! Helper function prototypes
CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void);


void setUp(void)
{
}

void tearDown(void)
{
    Simple_Float_Buffer = NULL;
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
    float simple_item;
    
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    simple_item = 67.;
    
    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        &simple_item
    );
    
    TEST_ASSERT_EQUAL(67., simple_item);
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

//! Helper functions

CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void) {
    CIRCULARBUFFER_TYPE* buf;
    buf = CircularBuffer_Create(sizeof(float));
    return buf;
}

#endif // TEST
