
#include "CircularBuffer.h"

#include <string.h>

//! Static variables and methods

static uint16_t Buffer_Size;
static CIRCULARBUTTER_ITEM_TYPE Buffer_Item;

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer);

//! Public implementations

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size) {
    Buffer_Size = 0;
    Buffer_Item = 0;
    return NULL;
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
    
    Buffer_Size = 0;
    memcpy(item, &Buffer_Item, GetItemSize(buffer));
    return true;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item) {
    Buffer_Size++;
    memcpy(&Buffer_Item, item, GetItemSize(buffer));
    return true;
}

//! Private implementations

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return (Buffer_Size == 0);
}

static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer) {
    return sizeof(CIRCULARBUTTER_ITEM_TYPE);
}