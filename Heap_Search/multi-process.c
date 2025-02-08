#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int searchItem_mp(int* heap, int idx, int n, int item) {
    if (idx >= n) return 0;

    if (item == *(heap + idx)) {
        printf("Hi, I'm a process who found the item on index: %d\n", idx);
        exit(0);
    }

    if (item < *(heap + idx)) exit(0);

    pid_t left_pid = fork();
    if (left_pid == 0) {
        searchItem_mp(heap, 2 * idx + 1, n, item);
        exit(0);
    }

    pid_t right_pid = fork();
    if (right_pid == 0) {
        searchItem_mp(heap, 2 * idx + 2, n, item);
        exit(0);
    }

    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);

    return 1;
}

void find_mp(int n, int *A, int q) {
    int *heap = calloc(n, sizeof(int));
    makeHeap(n, A, heap);

    searchItem_mp(heap, 0, n, q);
}
