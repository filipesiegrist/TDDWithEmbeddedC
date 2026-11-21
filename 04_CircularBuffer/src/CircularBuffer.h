#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef float CIRCULARBUTTER_ITEM_TYPE;
typedef struct {
    CIRCULARBUTTER_ITEM_TYPE* Buffer_Ptr;
    uint16_t Size;
    uint16_t Head;
    uint16_t Tail;
} CIRCULARBUFFER_TYPE;

#define CIRCULARBUFFER_CAPACITY 50


CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size, uint16_t capacity);

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer);
uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer);

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item);
bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item);

#endif // CIRCULARBUFFER_H
