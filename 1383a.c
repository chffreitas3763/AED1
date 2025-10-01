#include <stdio.h>

static int eh_valido(int g[9][9]) {
    // Verifica linhas
    for (int i = 0; i < 9; i++) {
        int mask = 0;
        for (int j = 0; j < 9; j++) {
            int x = g[i][j];
            if (x < 1 || x > 9) return 0;         // fora do intervalo
            int bit = 1 << x;
            if (mask & bit) return 0;              // repetido na linha
            mask |= bit;
        }
    }
    // Verifica colunas
    for (int j = 0; j < 9; j++) {
        int mask = 0;
        for (int i = 0; i < 9; i++) {
            int x = g[i][j];
            int bit = 1 << x;
            if (mask & bit) return 0;              // repetido na coluna
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
                    int bit = 1 << x;
                    if (mask & bit) return 0;      // repetido no bloco
                    mask |= bit;
                }
            }
        }
    }
    return 1; // passou por tudo
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    for (int k = 1; k <= n; k++) {
        int grid[9][9];
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                scanf("%d", &grid[i][j]);

        int ok = eh_valido(grid);

        printf("Instancia %d\n", k);
        if (ok) printf("SIM\n\n");
        else    printf("NAO\n\n");
    }
    return 0;
}
