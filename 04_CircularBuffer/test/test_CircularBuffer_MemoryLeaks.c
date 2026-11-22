#include "unity.h"

#include "CircularBuffer.h"
#include "mock_Memory.h"

#define SMALL_BUFFER_CAPACITY   2

void setUp(void)
{
}

void tearDown(void)
{
}

void test_GivenCreatedBuffer_WhenDestroyIsCalled_ThenFreesInternalArrayAndStructInOrder(void)
{
    CIRCULARBUFFER_TYPE fake_struct;
    float fake_data[SMALL_BUFFER_CAPACITY];
    CIRCULARBUFFER_TYPE* buf;

    Memory_Allocate_ExpectAndReturn(
        sizeof(CIRCULARBUFFER_TYPE),
        &fake_struct
    );
    Memory_Allocate_ExpectAndReturn(SMALL_BUFFER_CAPACITY * sizeof(float),
        fake_data
    );
    buf = CircularBuffer_Create(sizeof(float), SMALL_BUFFER_CAPACITY);

    Memory_Deallocate_Expect(fake_data);
    Memory_Deallocate_Expect(&fake_struct);
    CircularBuffer_Destroy(&buf);
}

void test_WhenStructAllocationFails_ThenReturnsNullWithoutLeaking(void)
{
    Memory_Allocate_ExpectAndReturn(sizeof(CIRCULARBUFFER_TYPE), NULL);

    CIRCULARBUFFER_TYPE* buf = CircularBuffer_Create(sizeof(float), SMALL_BUFFER_CAPACITY);

    TEST_ASSERT_NULL(buf);
}

void test_WhenDataArrayAllocationFails_ThenFreesStructAndReturnsNull(void)
{
    CIRCULARBUFFER_TYPE fake_struct;
    CIRCULARBUFFER_TYPE* buf;

    Memory_Allocate_ExpectAndReturn(sizeof(CIRCULARBUFFER_TYPE), &fake_struct);
    Memory_Allocate_ExpectAndReturn(SMALL_BUFFER_CAPACITY * sizeof(float), NULL);
    Memory_Deallocate_Expect(&fake_struct);

    buf = CircularBuffer_Create(
        sizeof(float),
        SMALL_BUFFER_CAPACITY
    );

    TEST_ASSERT_NULL(buf);
}

void test_GivenZeroCapacity_WhenCreate_ThenReturnNull(void)
{
    TEST_ASSERT_NULL(
        CircularBuffer_Create(sizeof(float), 0)
    );
}

void test_GivenZeroTypeSize_WhenCreate_ThenReturnNull(void)
{
    TEST_ASSERT_NULL(
        CircularBuffer_Create(0, SMALL_BUFFER_CAPACITY)
    );
}

void test_WhenAllocationSizeOverflowsSizeT_ThenReturnsNullWithoutAllocating(void)
{
    size_t overflowing_type_size = (SIZE_MAX / SMALL_BUFFER_CAPACITY) + 1;
    CIRCULARBUFFER_TYPE* buf;

    // Nenhuma expectativa de Memory_Allocate: se tentar alocar, o CMock falha o teste
    buf = CircularBuffer_Create(overflowing_type_size, SMALL_BUFFER_CAPACITY);

    TEST_ASSERT_NULL(buf);
}
