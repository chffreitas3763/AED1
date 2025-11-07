#include <stdio.h>

#define MAX_ID 100001  // ID máximo pode ser até 100000

int main() {
    int N;
    scanf("%d", &N);  // Número de pessoas inicialmente na fila

    int fila[50000];      // Vetor para armazenar a fila original
    int saiu[MAX_ID] = {0}; // Vetor para marcar quem saiu (todos iniciam com 0)

    // Lê os N identificadores da fila
    for (int i = 0; i < N; i++) {
        scanf("%d", &fila[i]);
    }

    int M;
    scanf("%d", &M);  // Número de pessoas que saíram da fila

    // Marca os IDs que saíram
    for (int i = 0; i < M; i++) {
        int id;
        scanf("%d", &id);
        if (id >= 0 && id < MAX_ID) {
            saiu[id] = 1;
        }
    }

    // Imprime os que ainda estão na fila, na ordem de chegada
    int primeiro = 1; // Flag para não imprimir espaço no início

    for (int i = 0; i < N; i++) {
        int id = fila[i];
        if (!saiu[id]) {
            if (!primeiro) {
                printf(" ");
            }
            printf("%d", id);
            primeiro = 0;
        }
    }

    printf("\n");

    return 0;
}
