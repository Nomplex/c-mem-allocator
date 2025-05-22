#include <stdio.h>
#include "nMem.h"

struct testStruct {
    int x;
    int y;
};

int main(void)
{

    printf("size of testStruct: %lu\n", sizeof(struct testStruct));
    struct testStruct *t = nMalloc(sizeof(struct testStruct));
    printMemoryPool();
    nFree(t);

    int *nInt = nMalloc(sizeof(int));
    printMemoryPool();
    nFree(nInt);

    return 0;
}
