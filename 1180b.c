#include <stdio.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int X[1000];      
    int *p = X;

    // Lê os N valores usando ponteiro
    for (int i = 0; i < N; ++i, ++p) {
        scanf("%d", p);   // p aponta para X[i]
    }

    // Encontra o menor valor usando ponteiros
    int *pmin = X;      
    for (p = X + 1; p < X + N; ++p) {
        if (*p < *pmin) pmin = p;
    }

    // Calcula a posição por aritmética de ponteiros
    int pos = (int)(pmin - X);

    printf("Menor valor: %d\n", *pmin);
    printf("Posicao: %d\n", pos);
    return 0;
}
