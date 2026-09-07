
#include "CircularBuffer.h"

#include <string.h>

static uint16_t Buffer_Size;
static float Buffer_Item;

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer);

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
    float out_item;

    if (item == NULL) return false;
    if (IsEmpty(buffer)) return false;
    
    Buffer_Size = 0;
    out_item = 2289;
    memcpy(item, &Buffer_Item, sizeof(float));
    return true;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item) {
    Buffer_Size = 1;
    memcpy(&Buffer_Item, item, sizeof(float));
    return true;
}

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return (Buffer_Size == 0);
}
