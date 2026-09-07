#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <stdint.h>
#include <stdbool.h>

typedef int CIRCULARBUFFER_TYPE;


CIRCULARBUFFER_TYPE* CircularBuffer_Create(size_t type_size);

bool CircularBuffer_IsEmpty(const CIRCULARBUFFER_TYPE* buffer);
bool CircularBuffer_IsFull(const CIRCULARBUFFER_TYPE* buffer);
uint16_t CircularBuffer_GetSize(const CIRCULARBUFFER_TYPE* buffer);

bool CircularBuffer_Dequeue(CIRCULARBUFFER_TYPE* buffer, void* item);

#endif // CIRCULARBUFFER_H
