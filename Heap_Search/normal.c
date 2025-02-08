// #include "heapify.c"

#include <stdio.h>
#include <stdlib.h>

void swapItems(int a_idx, int b_idx, int *heap)
{
    *(heap + a_idx) = *(heap + a_idx) ^ *(heap + b_idx);
    *(heap + b_idx) = *(heap + a_idx) ^ *(heap + b_idx);
    *(heap + a_idx) = *(heap + a_idx) ^ *(heap + b_idx);
}

void insertToHeap(int index, int *heap, int item)
{
    *(heap + index) = item;

    while (index > 0 && *(heap + ((index - 1) / 2)) > *(heap + index))
    {
        swapItems(index, (index - 1) / 2, heap);
        index = (index - 1) / 2;
    }
}


void makeHeap(int n, int *A, int* heap)
{
    for (size_t i = 0; i < n; i++)
        insertToHeap(i, heap, *(A + i));
}



void searchItem(int* heap, int idx, int n, int item)
{
    // printf("%d\n", *(heap + idx));
    if (item == *(heap + idx))
    {
        printf("Hi, I found the item on index: %d\n", idx);
    }

    if (idx * 2 <= n) searchItem(heap, idx * 2 + 1, n, item);
    if (idx * 2 + 1 <= n) searchItem(heap, idx * 2 + 2, n, item);

}

void find(int n, int *A, int q) {
    int *heap = calloc(n, sizeof(int));
    makeHeap(n, A, heap);

    searchItem(heap, 0, n, q);
}
