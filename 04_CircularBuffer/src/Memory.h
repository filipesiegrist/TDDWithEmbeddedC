
#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

void* Memory_Allocate(size_t size);
void Memory_Deallocate(void *memory_region);

#endif // MEMORY_H
