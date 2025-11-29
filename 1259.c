#include <stdio.h>
#include <stdlib.h>

int cmp_even(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;   // crescente
}

int cmp_odd(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return y - x;   // decrescente
}

int main() {
    int N;
    scanf("%d", &N);

    int *even = malloc(sizeof(int) * N);
    int *odd  = malloc(sizeof(int) * N);
    int ce = 0, co = 0;

    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        if (x % 2 == 0) even[ce++] = x;
        else odd[co++] = x;
    }

    qsort(even, ce, sizeof(int), cmp_even);
    qsort(odd,  co, sizeof(int), cmp_odd);

    for (int i = 0; i < ce; i++) printf("%d\n", even[i]);
    for (int i = 0; i < co; i++) printf("%d\n", odd[i]);

    free(even);
    free(odd);
    return 0;
}
