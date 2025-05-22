#include <unistd.h>
#include "nMem.h"

void *requestMemory(size_t size)
{
    void *ptr = sbrk(size);
    if (!ptr) {
        printf("No Pointer :(");
        exit(EXIT_FAILURE);
    }

    return ptr;
}
