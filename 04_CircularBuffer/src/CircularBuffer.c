
#include "CircularBuffer.h"
#include "Memory.h"

#include <string.h>

static bool IsFull(const CIRCULARBUFFER_TYPE* buffer);
static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer);
static CIRCULARBUTTER_ITEM_TYPE* GetHeadPosition(const CIRCULARBUFFER_TYPE* buffer);
static CIRCULARBUTTER_ITEM_TYPE* GetTailPosition(const CIRCULARBUFFER_TYPE* buffer);

//! Public implementations

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size, uint16_t capacity) {
    CIRCULARBUFFER_TYPE* new_buffer;

    //! Pre Condition: Having a positive capacity
    if (capacity <= 0) return NULL;

    //! Pre Condition: Having a valid type
    if (type_size <= 0) return NULL;

    //! Pre Condition: Allocated size not overflowing
    if (type_size > (SIZE_MAX / capacity)) return NULL;

    new_buffer = Memory_Allocate(sizeof(CIRCULARBUFFER_TYPE));

    //! Pre Condition: Could correcty allocate space for the Type
    if (new_buffer == NULL) return NULL;

    new_buffer->Head = 0;
    new_buffer->Tail = 0;
    new_buffer->Size = 0;
    new_buffer->Type_Size = type_size;
    new_buffer->Capacity = capacity;
    new_buffer->Storage_Ptr =
        Memory_Allocate(type_size*capacity);
    
    if (new_buffer->Storage_Ptr == NULL)
    {
        Memory_Deallocate(new_buffer);
        new_buffer = NULL;
    }

    return new_buffer;
}

void CircularBuffer_Destroy(CIRCULARBUFFER_TYPE** buffer_ptr) {
    //! Pre Condition: Having an address with the buffer pointer
    if (buffer_ptr == NULL) return;

    //! Pre Condition: Having a non-null buffer
    if (*buffer_ptr == NULL) return;

    Memory_Deallocate((*buffer_ptr)->Storage_Ptr);
    Memory_Deallocate(*buffer_ptr);

    *buffer_ptr = NULL;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return IsEmpty(buffer);
}

bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    return IsFull(buffer);
}

uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer) {
    if (buffer == NULL) return 0;
    return buffer->Size;
}

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item) {
    if (item == NULL) return false;
    if (IsEmpty(buffer)) return false;

    memcpy(item, GetTailPosition(buffer), GetItemSize(buffer));

    buffer->Tail = (buffer->Tail + 1) % buffer->Capacity;
    buffer->Size--;
    return true;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item) {
    //! Pre Condition: valid buffer
    if (buffer == NULL) return false;

    //! Pre Condition: Not full
    if (IsFull(buffer)) return false;
    
    //! Pre Condition: valid item
    if (item == NULL) return false;
    
    memcpy(GetHeadPosition(buffer), item, GetItemSize(buffer));
    buffer->Size++;
    buffer->Head = (buffer->Head + 1) % buffer->Capacity;
    return true;
}

//! Private implementations

static CIRCULARBUTTER_ITEM_TYPE* GetHeadPosition(const CIRCULARBUFFER_TYPE* buffer) {
    return buffer->Storage_Ptr+buffer->Head*buffer->Type_Size;
}

static CIRCULARBUTTER_ITEM_TYPE* GetTailPosition(const CIRCULARBUFFER_TYPE* buffer) {
    return buffer->Storage_Ptr+buffer->Tail*buffer->Type_Size;
}

static bool IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    if (buffer == NULL) return false;
    return (buffer->Size) >= buffer->Capacity;
}

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    if (buffer == NULL) return true;
    return (buffer->Size == 0);
}

static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer) {
    return buffer->Type_Size;
}
