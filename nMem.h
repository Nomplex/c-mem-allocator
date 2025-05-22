#ifndef NOM_MEM_H
#define NOM_MEM_H

#include <stdbool.h>
#include <stdlib.h>

// Memory block metadata
typedef struct memBlock {
    bool free;
    size_t size;
} mBlock;

void *requestMemory(size_t size);

#endif
