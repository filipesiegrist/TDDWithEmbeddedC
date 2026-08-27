
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    void* Stack_Items_Ptr;
    uint16_t Stack_Size;
    uint16_t Item_Size;
} DYNAMICSTACK_TYPE;

DYNAMICSTACK_TYPE* DynamicStack__Initialize(uint16_t type_size);

bool DynamicStack__IsEmpty(const DYNAMICSTACK_TYPE* stack);
uint16_t DynamicStack__GetSize(const DYNAMICSTACK_TYPE* stack);
bool DynamicStack__Push(DYNAMICSTACK_TYPE* stack, const void* item);
bool DynamicStack__Pop(DYNAMICSTACK_TYPE* stack, void* item);
void DynamicStack__Clear(DYNAMICSTACK_TYPE** stack);

#endif // DYNAMICSTACK_H
