#include "Memory.h"

void* Memory_Allocate(size_t size) {
    return malloc(size);
}

void Memory_Deallocate(void *memory_region) {
    free(memory_region);
}
