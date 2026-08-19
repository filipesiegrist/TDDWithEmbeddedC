
#ifndef STATICSTACK_H
#define STATICSTACK_H

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t GENERIC_TYPE;
#define GENERIC_TYPE_ERROR UINT16_MAX

#define STATICSTACK_SIZE    30

typedef struct {
    GENERIC_TYPE elements[STATICSTACK_SIZE];
    uint16_t top;
} STATICSTACK_TYPE;

STATICSTACK_TYPE StaticStack__Initialize();
bool StaticStack__IsEmpty(STATICSTACK_TYPE stack);
void StaticStack__Push(STATICSTACK_TYPE *stack, GENERIC_TYPE element);
GENERIC_TYPE StaticStack__Pop(STATICSTACK_TYPE *stack);

#endif // STATICSTACK_H
