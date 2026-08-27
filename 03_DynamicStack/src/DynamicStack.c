
#include "DynamicStack.h"

#include <stdlib.h>
#include <string.h>

#ifndef DYNAMIC_STACK_C_ 
#define DYNAMIC_STACK_C_


//! Helper functions
static bool IsEmpty(const DYNAMICSTACK_TYPE* stack);
static uint8_t GetItemSize(const DYNAMICSTACK_TYPE* stack);
static void* GetTopPtr(DYNAMICSTACK_TYPE* stack);
static void* GetNextPtr(DYNAMICSTACK_TYPE* stack);
static void* GetStackPtr(DYNAMICSTACK_TYPE* stack, uint16_t position);
static uint16_t StackSize(const DYNAMICSTACK_TYPE* stack);
static void UpdateCapacity(DYNAMICSTACK_TYPE* stack);

DYNAMICSTACK_TYPE* DynamicStack__Initialize(uint16_t type_size) {
    DYNAMICSTACK_TYPE* Stack_Ptr;
    Stack_Ptr = malloc(sizeof(DYNAMICSTACK_TYPE));
    Stack_Ptr->Stack_Size = 0;
    Stack_Ptr->Item_Size = type_size;
    Stack_Ptr->Stack_Items_Ptr = malloc(type_size);
    return Stack_Ptr;
}

bool DynamicStack__IsEmpty(const DYNAMICSTACK_TYPE* stack) {
    if (stack == NULL) return true;
    return IsEmpty(stack);
}

uint16_t DynamicStack__GetSize(const DYNAMICSTACK_TYPE* stack) {
    return StackSize(stack);
}

bool DynamicStack__Push(DYNAMICSTACK_TYPE* stack, const void* item) {
    if (stack == NULL || item == NULL) return false;
    
    memcpy(GetNextPtr(stack), item, GetItemSize(stack));
    stack->Stack_Size++;

    UpdateCapacity(stack);

    return true;
}

bool DynamicStack__Pop(DYNAMICSTACK_TYPE* stack, void* item) {
    bool return_value;
    
    if (IsEmpty(stack)) {
        return_value = false;
    }
    else {
        memcpy(item, GetTopPtr(stack), GetItemSize(stack));
        (stack->Stack_Size)--;
        UpdateCapacity(stack);
        return_value = true;
    }
    
    return return_value;
}

void DynamicStack__Clear(DYNAMICSTACK_TYPE** stack) {
    if (stack == NULL) return;
    free(*stack);
    *stack = NULL;
}

//! Private

static bool IsEmpty(const DYNAMICSTACK_TYPE* stack) {
    return (StackSize(stack) == 0);
}

static uint16_t StackSize(const DYNAMICSTACK_TYPE* stack) {
    if (stack == NULL) return 0;
    return (stack->Stack_Size);
}

static uint8_t GetItemSize(const DYNAMICSTACK_TYPE* stack) {
    return stack->Item_Size;
}

static void* GetStackPtr(DYNAMICSTACK_TYPE* stack, uint16_t position) {
    void* array_ptr;
    array_ptr = (void *) (stack->Stack_Items_Ptr);
    array_ptr += GetItemSize(stack)*(position);
    return array_ptr;
}

static void* GetTopPtr(DYNAMICSTACK_TYPE* stack) {
    return GetStackPtr(stack, StackSize(stack) - 1);
}

static void* GetNextPtr(DYNAMICSTACK_TYPE* stack) {
    return GetStackPtr(stack, StackSize(stack));
}

static void UpdateCapacity(DYNAMICSTACK_TYPE* stack) {
    uint16_t new_size;

    new_size = (stack->Stack_Size + 1)*GetItemSize(stack);
    stack->Stack_Items_Ptr = realloc(stack->Stack_Items_Ptr, new_size);
}



#endif // DYNAMIC_STACK_C_
