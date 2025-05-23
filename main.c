#include <stdio.h>
#include "nMem.h"

struct testStruct {
    int x;
    int y;
};

int main(void)
{
    struct testStruct *t = nMalloc(sizeof(struct testStruct) * 10);
    nFree(t);

    int *nInt = nMalloc(sizeof(int));
    printMemoryPool();
    int *nInt2 = nMalloc(sizeof(int));
    printMemoryPool();
    int *nInt3 = nMalloc(sizeof(int));
    // int *nInt3 = nMalloc(sizeof(int));
    printMemoryPool();
    nFree(nInt);
    nFree(nInt2);
    nFree(nInt3);

    return 0;
}
