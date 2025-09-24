#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int *X = (int *)malloc((size_t)N * sizeof(int));
    if (!X) return 0;

    for (int i = 0; i < N; ++i) {
        if (scanf("%d", &X[i]) != 1) { free(X); return 0; }
    }

    int menor = X[0];
    int pos = 0;
    for (int i = 1; i < N; ++i) {
        if (X[i] < menor) { menor = X[i]; pos = i; }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", pos);

    free(X);
    return 0;
}
