#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Memory block metadata
typedef struct memBlock {
    bool free;
    size_t size;
} mBlock;

void *requestMemory(size_t size)
{
    void *ptr = sbrk(size);
    if (!ptr) {
        printf("No Pointer :(");
        exit(EXIT_FAILURE);
    }

    return ptr;
}

int main(void)
{
    size_t totalSize = 1024 + sizeof(mBlock);
    mBlock *block = (mBlock *) requestMemory(totalSize);
    block->size = totalSize;
    block->free = false;

    printf("size of the mBlock struct: %lu\n", sizeof(mBlock));
    printf("size of new mBlock variable: %lu\n", block->size);

    return 0;
}
