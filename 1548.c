#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort (ordem decrescente)
int comparar_desc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int T; // número de casos de teste
    scanf("%d", &T);

    while (T--) {
        int M; // número de alunos
        scanf("%d", &M);

        int fila_original[1000];
        int fila_ordenada[1000];

        // Leitura da fila original
        for (int i = 0; i < M; i++) {
            scanf("%d", &fila_original[i]);
            fila_ordenada[i] = fila_original[i]; // cópia para ordenar
        }

        // Ordena a cópia em ordem decrescente
        qsort(fila_ordenada, M, sizeof(int), comparar_desc);

        // Conta quantos alunos não mudaram de posição
        int contador = 0;
        for (int i = 0; i < M; i++) {
            if (fila_original[i] == fila_ordenada[i]) {
                contador++;
            }
        }

        // Imprime o resultado do caso
        printf("%d\n", contador);
    }

    return 0;
}
