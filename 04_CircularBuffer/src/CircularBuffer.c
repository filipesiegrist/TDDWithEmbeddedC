
#include "CircularBuffer.h"

#include <string.h>

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size) {
    return NULL;
}

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return true;
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


