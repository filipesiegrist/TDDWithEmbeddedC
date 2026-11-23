
#ifdef TEST

#include "unity.h"
#include <string.h>

#include "CircularBuffer.h"
#include "Memory.h"


//! Custom Generic Types for Testing

typedef union {
    uint8_t raw_bytes[128];
    struct {
        uint8_t  device_address;
        uint8_t  register_map_version;
        uint16_t sequence_counter;
        uint32_t acquisition_timestamp_ms;
        float    temperature_celsius;
        float    pressure_hpa;
        uint16_t humidity_permille;
        uint8_t  sensor_status_flags;
        char     sensor_tag[16];
        uint8_t  reserved_payload[91];
        uint16_t crc16_checksum;
    } telemetry;
} I2c_Sensor_Frame_t;


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
static CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void);
static CIRCULARBUFFER_TYPE* GetSimpleFullBuffer(void);
static CIRCULARBUFFER_TYPE* GetEmptyBufferWithCustomCapacity(uint16_t capacity);
static CIRCULARBUFFER_TYPE* GetSingleItemBuffer(void);
static void FillBufferWithFloats(
    CIRCULARBUFFER_TYPE* buf,
    uint16_t count,
    float start_value
);

static I2c_Sensor_Frame_t GetEmptyI2cSensorFrame(void);
static I2c_Sensor_Frame_t GetRealisticI2cSensorFrame(
    float temperature_celsius,
    float pressure_hpa,
    uint16_t humidity_permille
);

//! Helper defines
#define CIRCULARBUFFER_NORMAL_CAPACITY 50
#define SMALL_BUFFER_CAPACITY   2


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

void test_GivenTwoBuffersCreated_WhenPushingToOne_ThenOtherRemainsEmpty(void)
{
    CIRCULARBUFFER_TYPE* second_float_buffer;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    second_float_buffer = GetSimpleEmptyBuffer();
    Float_Input_Item = 6755.009;
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void *) &Float_Input_Item
    );

    TEST_ASSERT_TRUE(
        CircularBuffer_IsEmpty(second_float_buffer)
    );
}

void test_GivenTwoBuffersWithDifferentSizes_WhenGetSizeIsCalled_ThenReturnRespectiveSizes(void)
{
    CIRCULARBUFFER_TYPE* second_float_buffer;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    second_float_buffer = GetSimpleEmptyBuffer();

    Float_Input_Item_1 = 10.0f;
    Float_Input_Item_2 = 20.0f;
    Float_Input_Item_3 = 30.0f;

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*)&Float_Input_Item_1
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*)&Float_Input_Item_2
    );
    (void) CircularBuffer_Queue(
        second_float_buffer,
        (void*)&Float_Input_Item_3
    );

    TEST_ASSERT_EQUAL_UINT16(
        2,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
    TEST_ASSERT_EQUAL_UINT16(
        1,
        CircularBuffer_GetSize(second_float_buffer)
    );
}

void test_GivenTwoBuffers_WhenInterleavingQueuesAndDequeues_ThenMaintainIndependentFifoOrder(void)
{
    CIRCULARBUFFER_TYPE* second_float_buffer;

    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    second_float_buffer = GetSimpleEmptyBuffer();

    Float_Input_Item_1 = 10.0f;
    Float_Input_Item_2 = 20.0f;
    Float_Input_Item_3 = 30.0f;

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*)&Float_Input_Item_1
    );
    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*)&Float_Input_Item_2
    );
    (void) CircularBuffer_Queue(
        second_float_buffer,
        (void*)&Float_Input_Item_3
    );

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*)&Float_Output_Item_1
    );
    (void) CircularBuffer_Dequeue(
        second_float_buffer,
        (void*)&Float_Output_Item_2
    );

    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_1, Float_Output_Item_1);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_3, Float_Output_Item_2);
}

void test_GivenBufferWithCertainSize_WhenAllItemsQueued_ThenIsFull(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    FillBufferWithFloats(
        Simple_Float_Buffer,
        CIRCULARBUFFER_NORMAL_CAPACITY, 
        1.0f
    );
    TEST_ASSERT_TRUE(
        CircularBuffer_IsFull(Simple_Float_Buffer)
    );
}

void test_GivenBufferWithSize2_When2ItemsQueued_ThenIsFull(void)
{
    Simple_Float_Buffer = GetSimpleFullBuffer();
    TEST_ASSERT_TRUE(
        CircularBuffer_IsFull(Simple_Float_Buffer)
    );
}

void test_GivenBufferWithSize60_When60ItemsQueued_ThenIsFull(void)
{
    Simple_Float_Buffer = GetEmptyBufferWithCustomCapacity(60);
    FillBufferWithFloats(
        Simple_Float_Buffer,
        60, 
        1.0f
    );
    TEST_ASSERT_TRUE(
        CircularBuffer_IsFull(Simple_Float_Buffer)
    );
}

void test_GivenFullBuffer_WhenQueue_ThenReturnFalse(void)
{
    Simple_Float_Buffer =
        GetEmptyBufferWithCustomCapacity(SMALL_BUFFER_CAPACITY);
    FillBufferWithFloats(
        Simple_Float_Buffer,
        SMALL_BUFFER_CAPACITY,
        1.0f
    );
    Float_Input_Item = 99.0f;

    TEST_ASSERT_FALSE(
        CircularBuffer_Queue(
            Simple_Float_Buffer,
            (void*) &Float_Input_Item
        )
    );
}

void test_GivenFullBuffer_WhenQueueAndDequeue_ThenRetrieveLastValidItem(void)
{
    Simple_Float_Buffer =
        GetEmptyBufferWithCustomCapacity(SMALL_BUFFER_CAPACITY);
    Float_Input_Item_1 = 10.0f;
    Float_Input_Item_2 = 20.0f;
    Float_Input_Item_3 = 99.0f;

    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*) &Float_Input_Item_1);
    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*) &Float_Input_Item_2);
    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*) &Float_Input_Item_3);

    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*) &Float_Output_Item_1);
    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*) &Float_Output_Item_2);

    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_1, Float_Output_Item_1);
    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_2, Float_Output_Item_2);
}

void test_GivenFullBuffer_WhenQueueAndDequeue_ThenDontRetrieveInvalidItem(void)
{
    Simple_Float_Buffer =
        GetEmptyBufferWithCustomCapacity(SMALL_BUFFER_CAPACITY);
    Float_Input_Item_1 = 10.0f;
    Float_Input_Item_2 = 20.0f;
    Float_Input_Item_3 = 99.0f;

    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*) &Float_Input_Item_1);
    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*) &Float_Input_Item_2);
    (void) CircularBuffer_Queue(Simple_Float_Buffer, (void*) &Float_Input_Item_3);

    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*) &Float_Output_Item_1);
    (void) CircularBuffer_Dequeue(Simple_Float_Buffer, (void*) &Float_Output_Item_2);

    TEST_ASSERT_EQUAL_FLOAT(Float_Input_Item_2, Float_Output_Item_2);
    TEST_ASSERT_NOT_EQUAL_FLOAT(Float_Input_Item_3, Float_Output_Item_2);
}

void test_GivenFullBuffer_WhenQueue_ThenSizeDoesNotIncrease(void)
{
    Simple_Float_Buffer = GetSimpleFullBuffer();

    (void) CircularBuffer_Queue(
        Simple_Float_Buffer,
        (void*) &Float_Input_Item
    );

    TEST_ASSERT_EQUAL_UINT16(
        SMALL_BUFFER_CAPACITY,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenFullBuffer_WhenDequeue_ThenItsNotFull(void)
{
    Simple_Float_Buffer = GetSimpleFullBuffer();

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );
    TEST_ASSERT_FALSE(
        CircularBuffer_IsFull(Simple_Float_Buffer)
    );
}

void test_GivenEmptyBuffer_WhenDequeue_ThenSizeRemainsZero(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();
    Float_Output_Item = 0.0f;

    (void) CircularBuffer_Dequeue(
        Simple_Float_Buffer,
        (void*) &Float_Output_Item
    );

    TEST_ASSERT_EQUAL_UINT16(
        0,
        CircularBuffer_GetSize(Simple_Float_Buffer)
    );
}

void test_GivenCreatedBuffer_WhenDestroyIsCalled_ThenSetsPointerToNull(void)
{
    Simple_Float_Buffer = GetSimpleEmptyBuffer();

    CircularBuffer_Destroy(&Simple_Float_Buffer);

    TEST_ASSERT_NULL(Simple_Float_Buffer);
}

void test_GivenPointerToNull_WhenDestroyIsCalled_ThenRemainsNull(void)
{
    Simple_Float_Buffer = NULL;
    CircularBuffer_Destroy(&Simple_Float_Buffer);
    TEST_ASSERT_NULL(Simple_Float_Buffer);
}

void test_WhenDestroyIsCalledWithNullAddress_ThenDoesNotCrash(void)
{
    //! Guard rail against passing NULL instead of &buffer_ptr
    CircularBuffer_Destroy(NULL);
}

//! Creation boundary & zero-size checks

//! Null pointer safety checks

void test_GivenNullBuffer_WhenIsEmpty_ThenReturnTrue(void)
{
    TEST_ASSERT_TRUE(
        CircularBuffer_IsEmpty(NULL)
    );
}

void test_GivenNullBuffer_WhenIsFull_ThenReturnFalse(void)
{
    TEST_ASSERT_FALSE(
        CircularBuffer_IsFull(NULL)
    );
}

void test_GivenNullBuffer_WhenGetSize_ThenReturnZero(void)
{
    TEST_ASSERT_EQUAL(
        0,
        CircularBuffer_GetSize(NULL)
    );
}

void test_GivenNullBuffer_WhenQueue_ThenReturnFalse(void)
{
    Float_Input_Item = 67.0f;
    TEST_ASSERT_FALSE(
        CircularBuffer_Queue(
            NULL,
            &Float_Input_Item
        )
    );
}

void test_GivenValidBuffer_WhenQueueWithNullItem_ThenReturnFalse(void)
{
    CIRCULARBUFFER_TYPE* buf;

    buf = GetSimpleEmptyBuffer();
    TEST_ASSERT_FALSE(
        CircularBuffer_Queue(
            buf,
            NULL
        )
    );
}

void test_GivenNullBuffer_WhenDequeue_ThenReturnFalse(void)
{
    Float_Input_Item = 67.0f;
    TEST_ASSERT_FALSE(
        CircularBuffer_Dequeue(
            NULL,
            &Float_Input_Item
        )
    );
}

//! Generic Type Support Tests

void test_GivenCharBuffer_WhenItemsAreQueuedAndDequeued_ThenReturnsThemInFifoOrder(void)
{
    CIRCULARBUFFER_TYPE* char_buf;
    const char in_1 = 'A';
    const char in_2 = 'B';
    const char in_3 = 'C';
    char out_1 = 0;
    char out_2 = 0;
    char out_3 = 0;

    char_buf = CircularBuffer_Create(sizeof(char), 3);

    (void) CircularBuffer_Queue(char_buf, (void*) &in_1);
    (void) CircularBuffer_Queue(char_buf, (void*) &in_2);
    (void) CircularBuffer_Queue(char_buf, (void*) &in_3);

    (void) CircularBuffer_Dequeue(char_buf, (void*) &out_1);
    (void) CircularBuffer_Dequeue(char_buf, (void*) &out_2);
    (void) CircularBuffer_Dequeue(char_buf, (void*) &out_3);

    TEST_ASSERT_EQUAL_CHAR(in_1, out_1);
    TEST_ASSERT_EQUAL_CHAR(in_2, out_2);
    TEST_ASSERT_EQUAL_CHAR(in_3, out_3);

    CircularBuffer_Destroy(&char_buf);
}

void test_GivenI2cSensorFrameBuffer_WhenFramesAreQueuedAndDequeued_ThenPreservesAllData(void)
{
    TEST_IGNORE_MESSAGE("Not implemented yet");
}

//! Helper functions

static CIRCULARBUFFER_TYPE* GetSimpleEmptyBuffer(void) {
    return GetEmptyBufferWithCustomCapacity(CIRCULARBUFFER_NORMAL_CAPACITY);
}

static CIRCULARBUFFER_TYPE* GetEmptyBufferWithCustomCapacity(uint16_t capacity) {
    CIRCULARBUFFER_TYPE* buf;
    buf = CircularBuffer_Create(sizeof(float), capacity);
    return buf;
}

static CIRCULARBUFFER_TYPE* GetSingleItemBuffer(void) {
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

static CIRCULARBUFFER_TYPE* GetSimpleFullBuffer(void) {
    CIRCULARBUFFER_TYPE* buf;

    buf = GetEmptyBufferWithCustomCapacity(SMALL_BUFFER_CAPACITY);
    FillBufferWithFloats(
        buf, 
        SMALL_BUFFER_CAPACITY, 
        1.0f
    );
    return buf;
}

static void FillBufferWithFloats(
    CIRCULARBUFFER_TYPE* buf,
    uint16_t count,
    float start_value
) {
    float val = start_value;
    for (uint16_t i = 0; i < count; i++) {
        (void) CircularBuffer_Queue(buf, (void*) &val);
        val += 1.0f;
    }
}

static I2c_Sensor_Frame_t GetEmptyI2cSensorFrame(void)
{
    I2c_Sensor_Frame_t frame;
    memset(&frame, 0, sizeof(I2c_Sensor_Frame_t));
    return frame;
}

static I2c_Sensor_Frame_t GetRealisticI2cSensorFrame(
    float temperature_celsius,
    float pressure_hpa,
    uint16_t humidity_permille
)
{
    I2c_Sensor_Frame_t frame = GetEmptyI2cSensorFrame();

    // Fixed protocol metadata & sensor identity
    frame.telemetry.device_address           = 0x76;        // Typical BME280/BMP280 I2C address
    frame.telemetry.register_map_version     = 0x02;
    frame.telemetry.sequence_counter         = 42;
    frame.telemetry.acquisition_timestamp_ms = 125480;
    frame.telemetry.sensor_status_flags      = 0x81;        // Bit 7: Data Ready | Bit 0: Calibrated
    strncpy(frame.telemetry.sensor_tag, "EVAP_CHAMBER_01", sizeof(frame.telemetry.sensor_tag) - 1);

    // Dynamic environmental readings
    frame.telemetry.temperature_celsius = temperature_celsius;
    frame.telemetry.pressure_hpa        = pressure_hpa;
    frame.telemetry.humidity_permille   = humidity_permille;

    // Deterministic pattern in reserved bytes to catch partial-copy bugs across all 128 bytes
    for (size_t i = 0; i < sizeof(frame.telemetry.reserved_payload); i++) {
        frame.telemetry.reserved_payload[i] = (uint8_t)(0xA0 + (i & 0x0F));
    }

    // Simple additive checksum over the first 126 bytes
    uint16_t checksum = 0;
    for (size_t i = 0; i < (sizeof(I2c_Sensor_Frame_t) - sizeof(uint16_t)); i++) {
        checksum += frame.raw_bytes[i];
    }
    frame.telemetry.crc16_checksum = checksum;

    return frame;
}

#endif // TEST
