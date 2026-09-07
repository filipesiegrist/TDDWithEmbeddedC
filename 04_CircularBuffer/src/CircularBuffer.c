
#include "CircularBuffer.h"

#include <string.h>

static bool Is_Empty;
static uint16_t Buffer_Size;

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size) {
    Is_Empty = true;
    Buffer_Size = 0;
    return NULL;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return Is_Empty;
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
    if (Is_Empty == true) return false;
    
    out_item = 2289;
    memcpy(item, &out_item, sizeof(float));
    return false;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, void* item) {

    Is_Empty = false;
    Buffer_Size = 1;
    return true;
}

