
#include "CircularBuffer.h"

#include <string.h>

static bool Is_Empty;

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size) {
    Is_Empty = true;
    return NULL;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return Is_Empty;
}

bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer) {
    return false;
}

uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer) {
    return 0;
}

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item) {
    // float new_item = 0;
    // memcpy(item, &new_item, sizeof(float));
    return false;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, void* item) {
    Is_Empty = false;
    return true;
}

