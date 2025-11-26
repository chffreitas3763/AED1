#include <stdio.h>

int adj[26][26];
int visited[26];
int V;

void dfs_collect(int u, int comp[], int *cnt) {
    visited[u] = 1;
    comp[(*cnt)++] = u;

    for (int v = 0; v < V; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs_collect(v, comp, cnt);
        }
    }
}

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        int tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
    }
}

// estrutura para guardar um componente inteiro
typedef struct {
    int nodes[26];
    int size;
    int smallest;
} Component;

int main() {
    int N;
    scanf("%d", &N);

    for (int tc = 1; tc <= N; tc++) {
        int E;
        scanf("%d %d", &V, &E);

        for (int i = 0; i < 26; i++) {
            visited[i] = 0;
            for (int j = 0; j < 26; j++) adj[i][j] = 0;
        }

        for (int i = 0; i < E; i++) {
            char a, b;
            scanf(" %c %c", &a, &b);
            int u = a - 'a';
            int v = b - 'a';
            adj[u][v] = adj[v][u] = 1;
        }

        // Coleta todos os componentes antes de imprimir
        Component comps[26];
        int compCount = 0;

        for (int u = 0; u < V; u++) {
            if (!visited[u]) {
                int tmp[26], cnt = 0;
                dfs_collect(u, tmp, &cnt);

                sort_array(tmp, cnt);

                comps[compCount].size = cnt;
                comps[compCount].smallest = tmp[0];
                for (int k = 0; k < cnt; k++) {
                    comps[compCount].nodes[k] = tmp[k];
                }
                compCount++;
            }
        }

        // Ordena os componentes pelo menor vértice lexicográfico
        for (int i = 0; i < compCount - 1; i++) {
            int min = i;
            for (int j = i + 1; j < compCount; j++) {
                if (comps[j].smallest < comps[min].smallest)
                    min = j;
            }
            if (min != i) {
                Component tmp = comps[i];
                comps[i] = comps[min];
                comps[min] = tmp;
            }
        }

        printf("Case #%d:\n", tc);

        //imprime os componentes na ordem correta
        for (int cc = 0; cc < compCount; cc++) {
            for (int k = 0; k < comps[cc].size; k++) {
                printf("%c,", (char)(comps[cc].nodes[k] + 'a'));
            }
            printf("\n");
        }

        printf("%d connected components\n\n", compCount);
    }

    return 0;
}
