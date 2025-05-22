#include <stdio.h>
#include <unistd.h>
#include "nMem.h"

mBlock *mPool = NULL;

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
    block->next = NULL;

    if (!mPool)
        mPool = block;
    else {
        mBlock *cur = mPool;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = block;
    }

    return (void *) block;
}

void nFree(void *ptr)
{
    if (!ptr) return;

    mBlock *block = (mBlock *) ptr;

    printf("Freeing block with size of: %lu\n", block->size);
    block->free = true;
}

void printMemoryPool(void)
{
    int i = 1;
    for (mBlock *cur = mPool; cur != NULL; cur = cur->next) {
        printf("%d:\nSize: %lu\nCurrently Free: %s\n\n",
                i++, cur->size, cur->free ? "True" : "False");
    }
}
