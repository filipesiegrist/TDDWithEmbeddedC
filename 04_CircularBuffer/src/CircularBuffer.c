
#include "CircularBuffer.h"
#include "Memory.h"

#include <string.h>

static bool IsFull(const CIRCULARBUFFER_TYPE* buffer);
static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer);
static CIRCULARBUTTER_ITEM_TYPE* GetHead(const CIRCULARBUFFER_TYPE* buffer);
static CIRCULARBUTTER_ITEM_TYPE* GetTail(const CIRCULARBUFFER_TYPE* buffer);

//! Public implementations

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size, uint16_t capacity) {
    CIRCULARBUFFER_TYPE* new_buffer;
    new_buffer = Memory_Allocate(sizeof(CIRCULARBUFFER_TYPE));

    new_buffer->Head = 0;
    new_buffer->Tail = 0;
    new_buffer->Size = 0;
    new_buffer->Capacity = capacity;
    new_buffer->Buffer_Ptr =
        Memory_Allocate(type_size*capacity);
    
    return new_buffer;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return IsEmpty(buffer);
}

bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    return IsFull(buffer);
}

uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer) {
    return buffer->Size;
}

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item) {
    if (item == NULL) return false;
    if (IsEmpty(buffer)) return false;

    memcpy(item, GetTail(buffer), GetItemSize(buffer));

    buffer->Tail++;
    buffer->Size--;
    return true;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item) {
    bool result;

    result = (IsFull(buffer))? false : true; 
    
    memcpy(GetHead(buffer), item, GetItemSize(buffer));
    buffer->Size++;
    buffer->Head++;
    return result;
}

//! Private implementations

static CIRCULARBUTTER_ITEM_TYPE* GetHead(const CIRCULARBUFFER_TYPE* buffer) {
    return &(buffer->Buffer_Ptr[buffer->Head]);
}

static CIRCULARBUTTER_ITEM_TYPE* GetTail(const CIRCULARBUFFER_TYPE* buffer) {
    return &(buffer->Buffer_Ptr[buffer->Tail]);
}

static bool IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    return (buffer->Size) >= buffer->Capacity;
}

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return (buffer->Size == 0);
}

static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer) {
    return sizeof(CIRCULARBUTTER_ITEM_TYPE);
}
