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
