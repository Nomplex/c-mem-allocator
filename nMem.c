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
    checkForJoinable();
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
    newBlock->free = true;
    newBlock->next = block->next;

    if (newBlock->next == NULL) {
        mPoolTail = newBlock;
    }

    block->size = size;
    block->next = newBlock;
}

size_t freeInARow(mBlock *start)
{
    // We could return larger than 3 here even though I only combine the first
    // available free with the next two. I could change that.
    size_t free = 0;
    for (mBlock *cur = start; cur != NULL && cur->free; cur = cur->next)
        free++;
    return free;
}

void checkForJoinable(void)
{
    // We look through the linked list start to finish.
    // If the first block and the next two blocks are free them combine them.

    mBlock *cur = mPoolHead;
    size_t free;

    while (cur != NULL) {
        free = freeInARow(cur);
        if (free >= 3)
            joinBlock(cur);
        cur = cur->next;
    }
}

void joinBlock(mBlock *block)
{
    size_t size2 = sizeof(mBlock) + block->next->size;
    size_t size3 = sizeof(mBlock) + block->next->next->size;

    block->size = block->size + size2 + size3;
    if (block->next->next == mPoolTail) {
        mPoolTail = block;
    }
    block->next = block->next->next->next;
}

void printMemoryPool(void)
{
    int i = 1;
    for (mBlock *cur = mPoolHead; cur != NULL; cur = cur->next) {
        printf("%d:\nSize: %lu\nCurrently Free: %s\n\n",
                i++, cur->size, cur->free ? "True" : "False");
    }
}
