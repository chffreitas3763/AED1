#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int u, v;
    int w;
} Edge;

int cmp_edge(const void *a, const void *b) {
    const Edge *ea = (const Edge*)a;
    const Edge *eb = (const Edge*)b;
    return ea->w - eb->w; // sort crescente por peso
}

/* Disjoint Set Union (Union-Find) com path compression e union by rank */
int *parent_arr;
int *rank_arr;

void make_set(int n) {
    parent_arr = (int*)malloc(n * sizeof(int));
    rank_arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        parent_arr[i] = i;
        rank_arr[i] = 0;
    }
}

int find_set(int x) {
    if (parent_arr[x] != x) parent_arr[x] = find_set(parent_arr[x]);
    return parent_arr[x];
}

void union_set(int a, int b) {
    int pa = find_set(a);
    int pb = find_set(b);
    if (pa == pb) return;
    if (rank_arr[pa] < rank_arr[pb]) {
        parent_arr[pa] = pb;
    } else if (rank_arr[pb] < rank_arr[pa]) {
        parent_arr[pb] = pa;
    } else {
        parent_arr[pb] = pa;
        rank_arr[pa]++;
    }
}

int main() {
    while (1) {
        int m, n; // m = número de junções (vertices), n = número de estradas (arestas)
        if (scanf("%d %d", &m, &n) != 2) return 0;
        if (m == 0 && n == 0) break;

        // aloca array de arestas
        Edge *edges = (Edge*)malloc(n * sizeof(Edge));
        ll total = 0; // soma total de todos os comprimentos

        for (int i = 0; i < n; i++) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            edges[i].u = x;
            edges[i].v = y;
            edges[i].w = z;
            total += (ll)z;
        }

        // ordenar arestas por peso crescente
        qsort(edges, n, sizeof(Edge), cmp_edge);

        // preparar DSU
        make_set(m);

        // executar Kruskal para construir MST e somar seus pesos
        ll mst = 0;
        int used_edges = 0;
        for (int i = 0; i < n && used_edges < m - 1; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if (find_set(u) != find_set(v)) {
                union_set(u, v);
                mst += (ll)w;
                used_edges++;
            }
        }

        // economia máxima = total - custo da MST
        ll economia = total - mst;
        printf("%lld\n", economia);

        // libera memória temporária
        free(edges);
        free(parent_arr);
        free(rank_arr);
    }

    return 0;
}
