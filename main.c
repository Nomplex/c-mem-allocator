#include <stdio.h>
#include "nMem.h"

int main(void)
{
    mBlock *block = nMalloc(1024);
    printMemoryPool();

    mBlock *block2 = nMalloc(512);
    printMemoryPool();

    nFree(block);
    nFree(block2);

    return 0;
}
