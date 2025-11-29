#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    int w;
} Edge;

int cmp(const void *a, const void *b) {
    Edge *e1 = (Edge*)a;
    Edge *e2 = (Edge*)b;
    return e1->w - e2->w;
}


static int parent[40000];
static int rankUF[40000];

void uf_init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rankUF[i] = 0;
    }
}

int uf_find(int x) {
    if (parent[x] != x)
        parent[x] = uf_find(parent[x]);
    return parent[x];
}

void uf_union(int a, int b) {
    a = uf_find(a);
    b = uf_find(b);
    if (a == b) return;

    if (rankUF[a] < rankUF[b])
        parent[a] = b;
    else if (rankUF[b] < rankUF[a])
        parent[b] = a;
    else {
        parent[b] = a;
        rankUF[a]++;
    }
}



int main() {
    int M, N;

    while (1) {
        scanf("%d %d", &M, &N);
        if (M == 0 && N == 0)
            break;

        Edge *edges = (Edge*)malloc(sizeof(Edge) * N);

        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].w);
        }

        // Ordenar por peso
        qsort(edges, N, sizeof(Edge), cmp);

        uf_init(M);

        long long total = 0;
        int chosen = 0;

        // KRUSKAL
        for (int i = 0; i < N && chosen < M - 1; i++) {
            if (uf_find(edges[i].x) != uf_find(edges[i].y)) {
                uf_union(edges[i].x, edges[i].y);
                total += edges[i].w;
                chosen++;
            }
        }

        printf("%lld\n", total);

        free(edges);
    }

    return 0;
}
