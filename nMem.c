#include <stdio.h>
#include <unistd.h>
#include "nMem.h"

void panic(char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

void *requestMemory(size_t size)
{
    size_t totalSize = size + sizeof(mBlock);
    void *ptr = sbrk(totalSize);
    if (!ptr)
        panic("No pointer returned from sbrk");

    return ptr;
}

void *nMalloc(size_t size)
{
    mBlock *block = (mBlock *) requestMemory(size);
    if (!block)
        panic("No block!");

    block->size = size;
    block->free = false;

    return (void *) block;
}

void nFree(void *ptr)
{
    if (!ptr) return;

    mBlock *block = (mBlock *) ptr;

    printf("Freeing Block of size: %lu\n", block->size);
    block->free = true;
}
