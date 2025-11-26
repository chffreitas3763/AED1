#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
} Edge;

int iguais(Edge e1, Edge e2) {
    return (e1.u == e2.u && e1.v == e2.v) ||
           (e1.u == e2.v && e1.v == e2.u);
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int start;
        scanf("%d", &start);

        int V, A;
        scanf("%d %d", &V, &A);

        // aloca dinamicamente todas as arestas lidas
        Edge *lidas = malloc(A * sizeof(Edge));
        Edge *unicas = malloc(A * sizeof(Edge));
        int unique_count = 0;

        for (int i = 0; i < A; i++) {
            scanf("%d %d", &lidas[i].u, &lidas[i].v);

            int repetida = 0;
            for (int j = 0; j < unique_count; j++) {
                if (iguais(unicas[j], lidas[i])) {
                    repetida = 1;
                    break;
                }
            }

            if (!repetida) {
                unicas[unique_count++] = lidas[i];
            }
        }

        free(lidas);
        free(unicas);

        printf("%d\n", unique_count * 2);
    }

    return 0;
}
