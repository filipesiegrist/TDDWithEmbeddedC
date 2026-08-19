
#include "StaticStack.h"


static bool IsEmpty(STATICSTACK_TYPE stack);
static bool IsFull(STATICSTACK_TYPE stack);

STATICSTACK_TYPE StaticStack__Initialize() {
    STATICSTACK_TYPE new_stack;
    uint16_t i;

    for (i = 0; i < STATICSTACK_SIZE; i++) {
        new_stack.elements[i] = GENERIC_TYPE_ERROR;
    }
    new_stack.top = 0;
    return new_stack;
}

bool StaticStack__IsEmpty(STATICSTACK_TYPE stack) {
    return IsEmpty(stack);
}

void StaticStack__Push(STATICSTACK_TYPE *stack, GENERIC_TYPE element) {
    if (IsFull(*stack) == false) {
        stack->elements[stack->top] = element;
        stack->top++;
    }
}

GENERIC_TYPE StaticStack__Pop(STATICSTACK_TYPE *stack) {
    GENERIC_TYPE popped_item;

    if (IsEmpty(*stack)) {
        popped_item = GENERIC_TYPE_ERROR;
    }
    else {
        stack->top--;

        popped_item = stack->elements[stack->top];
        stack->elements[stack->top] = GENERIC_TYPE_ERROR;
    }

    return popped_item;
}

static bool IsEmpty(STATICSTACK_TYPE stack) {
    bool is_empty;
    is_empty = (stack.top == 0)? true : false;
    return is_empty;
}

static bool IsFull(STATICSTACK_TYPE stack) {
    bool is_full;
    is_full = (stack.top == STATICSTACK_SIZE)? true : false;
    return is_full;
}