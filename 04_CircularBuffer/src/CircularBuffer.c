
#include "CircularBuffer.h"
#include "Memory.h"

#include <string.h>

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
    new_buffer->Buffer_Ptr =
        Memory_Allocate(type_size*CIRCULARBUFFER_CAPACITY);
    
    return new_buffer;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return IsEmpty(buffer);
}

bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    return (buffer->Size) >= CIRCULARBUFFER_CAPACITY;
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
    memcpy(GetHead(buffer), item, GetItemSize(buffer));
    buffer->Size++;
    buffer->Head++;
    return true;
}

//! Private implementations

static CIRCULARBUTTER_ITEM_TYPE* GetHead(const CIRCULARBUFFER_TYPE* buffer) {
    return &(buffer->Buffer_Ptr[buffer->Head]);
}

static CIRCULARBUTTER_ITEM_TYPE* GetTail(const CIRCULARBUFFER_TYPE* buffer) {
    return &(buffer->Buffer_Ptr[buffer->Tail]);
}

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return (buffer->Size == 0);
}

static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer) {
    return sizeof(CIRCULARBUTTER_ITEM_TYPE);
}
