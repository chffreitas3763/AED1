#include <stdio.h>
#include <stdlib.h>

static int eh_valido(int **g) {
    // Verifica linhas
    for (int i = 0; i < 9; i++) {
        int mask = 0;
        for (int j = 0; j < 9; j++) {
            int x = g[i][j];
            if (x < 1 || x > 9) return 0;
            int bit = 1 << x;
            if (mask & bit) return 0;
            mask |= bit;
        }
    }
    // Verifica colunas
    for (int j = 0; j < 9; j++) {
        int mask = 0;
        for (int i = 0; i < 9; i++) {
            int x = g[i][j];
            if (x < 1 || x > 9) return 0;
            int bit = 1 << x;
            if (mask & bit) return 0;
            mask |= bit;
        }
    }
    // Verifica blocos 3x3
    for (int bi = 0; bi < 9; bi += 3) {
        for (int bj = 0; bj < 9; bj += 3) {
            int mask = 0;
            for (int i = bi; i < bi + 3; i++) {
                for (int j = bj; j < bj + 3; j++) {
                    int x = g[i][j];
                    if (x < 1 || x > 9) return 0;
                    int bit = 1 << x;
                    if (mask & bit) return 0;
                    mask |= bit;
                }
            }
        }
    }
    return 1;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int k = 1; k <= n; k++) {
        // Aloca dinamicamente matriz 9x9
        int **grid = (int **)malloc(9 * sizeof(int *));
        if (!grid) return 0;
        for (int i = 0; i < 9; i++) {
            grid[i] = (int *)malloc(9 * sizeof(int));
            if (!grid[i]) {
                for (int t = 0; t < i; t++) free(grid[t]);
                free(grid);
                return 0;
            }
        }

        // Lê a matriz
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                scanf("%d", &grid[i][j]);

        int ok = eh_valido(grid);

        printf("Instancia %d\n", k);
        if (ok) printf("SIM\n\n");
        else    printf("NAO\n\n");

        // Libera memória
        for (int i = 0; i < 9; i++) free(grid[i]);
        free(grid);
    }
    return 0;
}
