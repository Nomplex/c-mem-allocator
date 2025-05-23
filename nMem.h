#ifndef NOM_MEM_H
#define NOM_MEM_H

#include <stdbool.h>
#include <stdlib.h>

// Memory block metadata
typedef struct memBlock {
    bool free;
    size_t size;
    struct memBlock *next;
} mBlock;

void *requestMemory(size_t size);
void *nMalloc(size_t size);
void nFree(void *ptr);
void *findFreeBlock(size_t size);
bool canSplitBlock(mBlock *block, size_t size);
void splitBlock(mBlock *block, size_t size);
void printMemoryPool(void);

#endif
