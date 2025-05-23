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
    mBlock *block = findFreeBlock(size);
    if (block) {
        if (canSplitBlock(block, size))
            splitBlock(block, size);
        block->free = false;
        return (void *) (block + 1);
    }

    block = (mBlock *) requestMemory(size);
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
    block->free = true;
    printf("Freeing block with size of: %lu\n", block->size);
}

void *findFreeBlock(size_t size)
{
    for (mBlock *cur = mPoolHead; cur != NULL; cur = cur->next)
        if (cur->free && cur->size >= size)
            return cur;

    return NULL;
}

bool canSplitBlock(mBlock *block, size_t size)
{
    // I'm just going to use the size of an int as an arbitrary size
    size_t minSize = sizeof(mBlock) + sizeof(int);
    size_t reqSize = sizeof(mBlock) + size;

    return (block->size >= reqSize + minSize);

    // My old return that underflowed... :(
    // return (block->size - reqSize >= minSize);
}

void splitBlock(mBlock *block, size_t size)
{
    size_t reqSize = sizeof(mBlock) + size;

    // Using the cast to char * to do a byte offset.
    mBlock *newBlock = (mBlock *) ((char *) block + (sizeof(mBlock) + size));
    newBlock->size = block->size - reqSize;
    newBlock->free = false;
    newBlock->next = block->next;

    block->size = size;
    block->next = newBlock;
}

void printMemoryPool(void)
{
    int i = 1;
    for (mBlock *cur = mPoolHead; cur != NULL; cur = cur->next) {
        printf("%d:\nSize: %lu\nCurrently Free: %s\n\n",
                i++, cur->size, cur->free ? "True" : "False");
    }
}
