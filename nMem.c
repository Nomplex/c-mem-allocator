#include <stdio.h>
#include <unistd.h>
#include "nMem.h"

mBlock *mPoolHead = NULL;
mBlock *mPoolTail = NULL;

void panic(char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

void *requestMemory(size_t size)
{
    size_t totalSize = sizeof(mBlock) + size;
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

    if (!mPoolHead) {
        mPoolHead = mPoolTail = block;
    } else {
        mPoolTail->next = block;
        mPoolTail = block;
    }

    return (void *) (block + 1);
}

void nFree(void *ptr)
{
    if (!ptr) return;

    mBlock *block = (mBlock *) ptr - 1;

    printf("Freeing block with size of: %lu\n", block->size);
    block->free = true;
}

void printMemoryPool(void)
{
    int i = 1;
    for (mBlock *cur = mPoolHead; cur != NULL; cur = cur->next) {
        printf("%d:\nSize: %lu\nCurrently Free: %s\n\n",
                i++, cur->size, cur->free ? "True" : "False");
    }
}
