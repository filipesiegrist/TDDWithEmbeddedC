#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef float CIRCULARBUTTER_ITEM_TYPE;
typedef struct {
    CIRCULARBUTTER_ITEM_TYPE* Storage_Ptr;
    uint16_t Size;
    uint16_t Head;
    uint16_t Tail;
    uint16_t Capacity;
} CIRCULARBUFFER_TYPE;


CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size, uint16_t capacity);
void CircularBuffer_Destroy(CIRCULARBUFFER_TYPE** buffer_ptr);

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer);
uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer);

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item);
bool CircularBuffer_Queue(CIRCULARBUFFER_TYPE* buffer, const void* item);

#endif // CIRCULARBUFFER_H
