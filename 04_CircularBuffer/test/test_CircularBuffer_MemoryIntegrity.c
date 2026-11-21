#include "unity.h"
#include <string.h>

#include "CircularBuffer.h"
#include "mock_Memory.h"

#define MAX_TEST_SLOTS 10

static CIRCULARBUFFER_TYPE Fake_Buffer_Struct;
static float Fake_Data_Array[MAX_TEST_SLOTS];

static void* FakeMemory_Allocate(size_t size, int cmock_num_calls)
{
    (void) size;

    if (cmock_num_calls == 0) {
        return &Fake_Buffer_Struct;
    }

    return Fake_Data_Array;
}

void setUp(void)
{
    memset(&Fake_Buffer_Struct, 0, sizeof(Fake_Buffer_Struct));
    memset(Fake_Data_Array, 0, sizeof(Fake_Data_Array));

    Memory_Allocate_StubWithCallback(FakeMemory_Allocate);
}

void tearDown(void)
{
}

//! Fake Characterization tests

void test_FakeMemoryAllocate_WhenCalledTwice_ThenReturnsStructAndDataArrayPointers(void)
{
    CIRCULARBUFFER_TYPE* returned_struct_ptr = NULL;
    float* returned_array_ptr = NULL;

    // 1st call: should return the address of Fake_Buffer_Struct
    returned_struct_ptr = Memory_Allocate(sizeof(CIRCULARBUFFER_TYPE));

    // 2nd call: should return the base address of Fake_Data_Array
    returned_array_ptr = Memory_Allocate(2 * sizeof(float));

    // Verify exact pointer addresses
    TEST_ASSERT_EQUAL_PTR(&Fake_Buffer_Struct, returned_struct_ptr);
    TEST_ASSERT_EQUAL_PTR(Fake_Data_Array, returned_array_ptr);

    // Write directly through the returned pointers and inspect the fake internals
    returned_struct_ptr->Capacity = 2;
    returned_array_ptr[0] = 10.0f;
    returned_array_ptr[1] = 20.0f;

    TEST_ASSERT_EQUAL_UINT16(2, Fake_Buffer_Struct.Capacity);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, Fake_Data_Array[0]);
    TEST_ASSERT_EQUAL_FLOAT(20.0f, Fake_Data_Array[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Fake_Data_Array[2]);
}

//! Memory Integrity Tests

void test_GivenCapacity2_WhenTwoItemsAreQueued_ThenDataIsStoredInAllocatedMemory(void)
{
    float in_1 = 10.0f;
    float in_2 = 20.0f;

    CIRCULARBUFFER_TYPE* buf = CircularBuffer_Create(sizeof(float), 2);

    (void) CircularBuffer_Queue(buf, &in_1);
    (void) CircularBuffer_Queue(buf, &in_2);

    TEST_ASSERT_EQUAL_FLOAT(10.0f, Fake_Data_Array[0]);
    TEST_ASSERT_EQUAL_FLOAT(20.0f, Fake_Data_Array[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Fake_Data_Array[2]);
}

void test_GivenCapacity2_WhenWrappingAroundOnQueue_ThenWrapsHeadAndDoesNotOverflowArray(void)
{
    float in_1 = 10.0f;
    float in_2 = 20.0f;
    float in_3 = 30.0f;
    float out_item = 0.0f;

    CIRCULARBUFFER_TYPE* buf = CircularBuffer_Create(sizeof(float), 2);

    (void) CircularBuffer_Queue(buf, &in_1);
    (void) CircularBuffer_Queue(buf, &in_2);
    (void) CircularBuffer_Dequeue(buf, &out_item);
    (void) CircularBuffer_Queue(buf, &in_3);

    // Inspect allocated data array boundaries
    TEST_ASSERT_EQUAL_FLOAT(30.0f, Fake_Data_Array[0]);
    TEST_ASSERT_EQUAL_FLOAT(20.0f, Fake_Data_Array[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, Fake_Data_Array[2]);
}

void test_GivenCapacity2_WhenWrappingAroundOnDequeue_ThenReadsFromWrappedIndexAndDoesNotReadOutOfBounds(void)
{
    float in_1 = 10.0f;
    float in_2 = 20.0f;
    float in_3 = 30.0f;
    float out_1 = 0.0f;
    float out_2 = 0.0f;
    float out_3 = 0.0f;

    CIRCULARBUFFER_TYPE* buf = CircularBuffer_Create(sizeof(float), 2);

    (void) CircularBuffer_Queue(buf, &in_1);
    (void) CircularBuffer_Queue(buf, &in_2);
    (void) CircularBuffer_Dequeue(buf, &out_1);
    (void) CircularBuffer_Dequeue(buf, &out_2);

    (void) CircularBuffer_Queue(buf, &in_3);
    (void) CircularBuffer_Dequeue(buf, &out_3);

    TEST_ASSERT_EQUAL_FLOAT(30.0f, out_3);
}