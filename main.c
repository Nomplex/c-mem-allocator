#include <stdio.h>
#include "nMem.h"

int main(void)
{
    mBlock *block = nMalloc(1024);

    printf("size of the mBlock struct: %lu\n", sizeof(mBlock));
    printf("size of new mBlock variable: %lu\n", block->size);

    nFree(block);

    return 0;
}
