
#include "CircularBuffer.h"
#include "Memory.h"

#include <string.h>

//! Static variables and methods

static uint16_t Buffer_Size;
static uint16_t Head;
static uint16_t Tail;

static CIRCULARBUFFER_TYPE* Static_Buffer_Ptr;

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer);
static CIRCULARBUTTER_ITEM_TYPE* GetHead(const CIRCULARBUFFER_TYPE* buffer);
static CIRCULARBUTTER_ITEM_TYPE* GetTail(const CIRCULARBUFFER_TYPE* buffer);

//! Public implementations

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size) {
    Buffer_Size = 0;
    Head = 0;
    Tail = 0;
    Static_Buffer_Ptr = Memory_Allocate(sizeof(CIRCULARBUFFER_TYPE));
    Static_Buffer_Ptr->Buffer_Ptr =
        Memory_Allocate(type_size*CIRCULARBUFFER_CAPACITY);
    
    return Static_Buffer_Ptr;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return IsEmpty(buffer);
}

bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    return false;
}

uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer) {
    return Buffer_Size;
}

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item) {
    if (item == NULL) return false;
    if (IsEmpty(buffer)) return false;
    
    memcpy(item, GetTail(buffer), GetItemSize(buffer));

    Tail++;
    Buffer_Size--;
    return true;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item) {
    memcpy(GetHead(buffer), item, GetItemSize(buffer));
    Buffer_Size++;
    Head++;
    return true;
}

//! Private implementations

static CIRCULARBUTTER_ITEM_TYPE* GetHead(const CIRCULARBUFFER_TYPE* buffer) {
    return &(buffer->Buffer_Ptr[Head]);
}

static CIRCULARBUTTER_ITEM_TYPE* GetTail(const CIRCULARBUFFER_TYPE* buffer) {
    return &(buffer->Buffer_Ptr[Tail]);
}

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return (Buffer_Size == 0);
}

static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer) {
    return sizeof(CIRCULARBUTTER_ITEM_TYPE);
}
