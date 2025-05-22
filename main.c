#include <stdio.h>
#include "nMem.h"

int main(void)
{
    int *nInt = nMalloc(sizeof(int));
    *nInt = 42;
    printf("nInt: %d\n", *nInt);

    float *nFloat = nMalloc(sizeof(float));
    *nFloat = 42.42;
    printf("nFloat: %.2f\n", *nFloat);

    printMemoryPool();
    nFree(nInt);
    nFree(nFloat);

    return 0;
}
