
#include "CircularBuffer.h"

#include <string.h>

//! Static variables and methods

static uint16_t Buffer_Size;
static uint16_t Head;
static uint16_t Tail;
static CIRCULARBUTTER_ITEM_TYPE Buffer_Array[CIRCULARBUFFER_CAPACITY];

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer);

//! Public implementations

CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size) {
    Buffer_Size = 0;
    Head = 0;
    Tail = 0;
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
    
    memcpy(item, &Buffer_Array[Tail], GetItemSize(buffer));

    Buffer_Array[0] = Buffer_Array[1];
    Tail++;
    Buffer_Size--;
    return true;
}

bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item) {
    memcpy(&Buffer_Array[Head], item, GetItemSize(buffer));
    Buffer_Size++;
    Head++;
    return true;
}

//! Private implementations

static bool IsEmpty(const CIRCULARBUFFER_TYPE* buffer) {
    return (Buffer_Size == 0);
}

static size_t GetItemSize(const CIRCULARBUFFER_TYPE* buffer) {
    return sizeof(CIRCULARBUTTER_ITEM_TYPE);
}