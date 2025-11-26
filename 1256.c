#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    while (N--) {
        int M, C;
        scanf("%d %d", &M, &C);

        // Estrutura: vetores de listas
        int table[100][200];   // M <= 100, C <= 200
        int size[100] = {0};

        // Inserções
        for (int i = 0; i < C; i++) {
            int key;
            scanf("%d", &key);
            int idx = key % M;
            table[idx][ size[idx]++ ] = key;
        }

        // Impressão
        for (int i = 0; i < M; i++) {
            printf("%d ->", i);
            for (int j = 0; j < size[i]; j++) {
                printf(" %d ->", table[i][j]);
            }
            printf(" \\\n");  // barra invertida final
        }

        if (N) printf("\n"); // linha em branco entre casos, mas não depois do último
    }

    return 0;
}
