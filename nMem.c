#include <stdio.h>
#include <unistd.h>
#include "nMem.h"

void panic(char *message) {
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
