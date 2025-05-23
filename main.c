#include <stdio.h>
#include "nMem.h"

struct testStruct {
    int x;
    int y;
};

int main(void)
{
    printf("Size of header: %lu", sizeof(mBlock));
    struct testStruct *t = nMalloc(sizeof(struct testStruct) * 10);
    nFree(t);

    int *nInt = nMalloc(sizeof(int));
    printMemoryPool();
    nFree(nInt);

    return 0;
}
