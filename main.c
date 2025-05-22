#include <stdio.h>
#include "nMem.h"

int main(void)
{
    mBlock *block = (mBlock *) requestMemory(1024);
    block->size = 1024 + sizeof(mBlock);
    block->free = false;

    printf("size of the mBlock struct: %lu\n", sizeof(mBlock));
    printf("size of new mBlock variable: %lu\n", block->size);

    return 0;
}
