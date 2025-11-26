#include <stdio.h>
#include <string.h>

#define INF 1000000000
#define MAXN 260
#define MAXM 60000  

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], edge_count;

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

int dist[MAXN], used[MAXN];

int extract_min(int n) {
    int best = -1;
    for (int i = 0; i < n; i++) {
        if (!used[i] && (best == -1 || dist[i] < dist[best])) best = i;
    }
    return best;
}

int main() {
    int N, M, C, K;
    while (scanf("%d %d %d %d", &N, &M, &C, &K) == 4) {
        if (N==0 && M==0 && C==0 && K==0) break;

        edge_count = 0;
        for (int i = 0; i < N; i++) head[i] = -1;

        for (int i = 0; i < M; i++) {
            int u, v, p;
            scanf("%d %d %d", &u, &v, &p);

            if (u >= C && v >= C) {
                // ambos fora da rota: bidirecional
                add_edge(u, v, p);
                add_edge(v, u, p);
            } else if (u < C && v < C) {
                // ambos na rota: só permitimos movimento i -> i+1
                if (v == u + 1) add_edge(u, v, p);
                if (u == v + 1) add_edge(v, u, p);
            } else {
                // um está na rota e outro fora
                if (u < C && v >= C) {
                    // u está na rota, v fora -> só permitir v -> u (entrar na rota)
                    add_edge(v, u, p);
                } else if (v < C && u >= C) {
                    // v está na rota, u fora -> só permitir u -> v (entrar na rota)
                    add_edge(u, v, p);
                }
            }
        }

        // Dijkstra simples O(N^2) suficiente (N <= 250)
        for (int i = 0; i < N; i++) {
            dist[i] = INF;
            used[i] = 0;
        }
        dist[K] = 0;

        for (int it = 0; it < N; it++) {
            int u = extract_min(N);
            if (u == -1 || dist[u] == INF) break;
            used[u] = 1;
            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].v;
                int w = edges[e].w;
                if (dist[u] + w < dist[v]) dist[v] = dist[u] + w;
            }
        }

        printf("%d\n", dist[C-1]);
    }
    return 0;
}
