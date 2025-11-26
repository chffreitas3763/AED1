#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 510
#define MAXE 250000
#define INF 1000000000

// Grafo original
int head[MAXN], to[MAXE], w[MAXE], nextE[MAXE], ec;

// Para Tarjan SCC
int disc[MAXN], low[MAXN], st[MAXN], inStack[MAXN];
int sccId[MAXN], sccCount, timeD, top;

// Grafo condensado
int head2[MAXN], to2[MAXE], w2[MAXE], nextE2[MAXE], ec2;

// Dijkstra
int dist[MAXN], used[MAXN];

void add_edge(int u, int v, int cost) {
    to[ec] = v;
    w[ec] = cost;
    nextE[ec] = head[u];
    head[u] = ec++;
}

void add_edge2(int u, int v, int cost) {
    to2[ec2] = v;
    w2[ec2] = cost;
    nextE2[ec2] = head2[u];
    head2[u] = ec2++;
}

void tarjan(int u) {
    disc[u] = low[u] = ++timeD;
    st[top++] = u;
    inStack[u] = 1;

    for (int e = head[u]; e != -1; e = nextE[e]) {
        int v = to[e];
        if (!disc[v]) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (inStack[v]) {
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }

    if (low[u] == disc[u]) {
        while (1) {
            int v = st[--top];
            inStack[v] = 0;
            sccId[v] = sccCount;
            if (v == u) break;
        }
        sccCount++;
    }
}

int extract_min(int n) {
    int best = -1;
    for (int i = 0; i < n; i++) {
        if (!used[i] && (best == -1 || dist[i] < dist[best]))
            best = i;
    }
    return best;
}

int main() {
    int N, E;

    while (scanf("%d %d", &N, &E) && (N || E)) {
        // reset
        ec = 0;
        memset(head, -1, sizeof(head));

        // read edges
        for (int i = 0; i < E; i++) {
            int X, Y, H;
            scanf("%d %d %d", &X, &Y, &H);
            add_edge(X - 1, Y - 1, H);
        }

        // reset Tarjan
        memset(disc, 0, sizeof(disc));
        memset(inStack, 0, sizeof(inStack));
        top = 0;
        timeD = 0;
        sccCount = 0;

        // run SCC
        for (int i = 0; i < N; i++) {
            if (!disc[i]) tarjan(i);
        }

        // build condensation graph
        ec2 = 0;
        memset(head2, -1, sizeof(head2));

        for (int u = 0; u < N; u++) {
            for (int e = head[u]; e != -1; e = nextE[e]) {
                int v = to[e];
                if (sccId[u] == sccId[v]) {
                    // edge inside SCC = cost 0
                    add_edge2(sccId[u], sccId[v], 0);
                } else {
                    // edge between SCCs = original cost
                    add_edge2(sccId[u], sccId[v], w[e]);
                }
            }
        }

        int K;
        scanf("%d", &K);

        while (K--) {
            int O, D;
            scanf("%d %d", &O, &D);
            O--; D--;

            int sO = sccId[O];
            int sD = sccId[D];

            // Dijkstra
            for (int i = 0; i < sccCount; i++) {
                dist[i] = INF;
                used[i] = 0;
            }
            dist[sO] = 0;

            for (int i = 0; i < sccCount; i++) {
                int u = extract_min(sccCount);
                if (u == -1 || dist[u] == INF) break;
                used[u] = 1;

                for (int e = head2[u]; e != -1; e = nextE2[e]) {
                    int v = to2[e];
                    int cost = w2[e];
                    if (dist[u] + cost < dist[v]) {
                        dist[v] = dist[u] + cost;
                    }
                }
            }

            if (dist[sD] == INF)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", dist[sD]);
        }

        printf("\n");
    }

    return 0;
}
