#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int* heap;
    int idx;
    int n;
    int item;
    int* found_flag;
} Arguments;

void* searchItem_mt(void* args)
{
    Arguments *argument = (Arguments*) args;
    int* heap = argument->heap;
    int idx = argument->idx;
    int n = argument->n;
    int item = argument->item;
    int* found_flag = argument->found_flag;

    if (*found_flag || idx >= n) pthread_exit(NULL);

    if (item == *(heap + idx)) 
    {
        printf("Hi, I'm a thread who found the item on index: %d\n", idx);
        *found_flag = 1;
        pthread_exit(NULL);
    }

    if (item < *(heap + idx))
        pthread_exit(NULL);

    pthread_t t1, t2;
    int t1_created = 0, t2_created = 0;

    if (idx * 2 + 1 < n && !*found_flag) 
    {
        Arguments *argChild1 = malloc(sizeof(Arguments));
        *argChild1 = (Arguments){heap, idx * 2 + 1, n, item, found_flag};
        t1_created = (pthread_create(&t1, NULL, searchItem_mt, argChild1) == 0);
    }

    if (idx * 2 + 2 < n && !*found_flag) 
    {
        Arguments *argChild2 = malloc(sizeof(Arguments));
        *argChild2 = (Arguments){heap, idx * 2 + 2, n, item, found_flag};
        t2_created = (pthread_create(&t2, NULL, searchItem_mt, argChild2) == 0);
    }

    if (t1_created) pthread_join(t1, NULL);
    if (t2_created) pthread_join(t2, NULL);

    free(argument);
    pthread_exit(NULL);
}

void find_mt(int n, int *A, int q) {
    int *heap = calloc(n, sizeof(int));
    makeHeap(n, A, heap);

    pthread_t tMain;
    int found_flag = 0;
    Arguments *argMain = malloc(sizeof(Arguments));
    *argMain = (Arguments){heap, 0, n, q, &found_flag};
    
    pthread_create(&tMain, NULL, searchItem_mt, argMain);
    pthread_join(tMain, NULL);

    if (!found_flag) 
        printf("Did not found the item.\n");

    free(heap);
}

