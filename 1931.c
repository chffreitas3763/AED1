#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000000000LL

typedef long long ll;

typedef struct {
    int v;
    int w;
} Edge;

typedef struct {
    ll dist;
    int u;
} HeapNode;

Edge *adj[20005];
int deg[20005];
int C, V;


HeapNode heap[400000];
int hsize = 0;

void heap_push(ll d, int u) {
    int i = ++hsize;
    heap[i].dist = d;
    heap[i].u = u;
    while (i > 1 && heap[i].dist < heap[i/2].dist) {
        HeapNode t = heap[i];
        heap[i] = heap[i/2];
        heap[i/2] = t;
        i /= 2;
    }
}

HeapNode heap_pop() {
    HeapNode ret = heap[1];
    heap[1] = heap[hsize--];
    int i = 1;

    while (1) {
        int l = i*2, r = l+1, smallest = i;
        if (l <= hsize && heap[l].dist < heap[smallest].dist) smallest = l;
        if (r <= hsize && heap[r].dist < heap[smallest].dist) smallest = r;
        if (smallest == i) break;

        HeapNode t = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = t;
        i = smallest;
    }
    return ret;
}

int heap_empty() { return hsize == 0; }

// ------------------------------------

ll dist[20005][2];  // dist[cidade][paridade]

int main() {
    while (1) {
        if (scanf("%d %d", &C, &V) != 2) return 0;
        if (C == 0 && V == 0) break;

        for (int i = 1; i <= C; i++) {
            adj[i] = NULL;
            deg[i] = 0;
        }

        for (int i = 0; i < V; i++) {
            int a, b, g;
            scanf("%d %d %d", &a, &b, &g);
            // add undirected
            adj[a] = realloc(adj[a], (deg[a] + 1) * sizeof(Edge));
            adj[a][deg[a]].v = b;
            adj[a][deg[a]].w = g;
            deg[a]++;

            adj[b] = realloc(adj[b], (deg[b] + 1) * sizeof(Edge));
            adj[b][deg[b]].v = a;
            adj[b][deg[b]].w = g;
            deg[b]++;
        }

        // Dijkstra nos estados
        for (int i = 1; i <= C; i++) {
            dist[i][0] = INF;
            dist[i][1] = INF;
        }

        hsize = 0;
        dist[1][0] = 0;
        heap_push(0, 1*2 + 0);  // encode: id = cidade*2 + paridade

        while (!heap_empty()) {
            HeapNode hn = heap_pop();
            ll d = hn.dist;
            int code = hn.u;
            int u = code / 2;
            int p = code % 2;

            if (d != dist[u][p]) continue;
            if (u == C && p == 0) break; // chegando com paridade par

            for (int i = 0; i < deg[u]; i++) {
                int v = adj[u][i].v;
                int w = adj[u][i].w;
                int np = 1 - p; // inverte por usar mais 1 pedágio

                if (dist[v][np] > d + w) {
                    dist[v][np] = d + w;
                    heap_push(dist[v][np], v*2 + np);
                }
            }
        }

        ll ans = dist[C][0];
        if (ans == INF) ans = -1;

        printf("%lld\n", ans);
    }

    return 0;
}
