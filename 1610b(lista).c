#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10005

typedef struct No {
    int valor;
    struct No* prox;
} No;

No* grafo[MAX];
int visitado[MAX];
int ciclo;
int N;

void inserir_aresta(int u, int v) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = v;
    novo->prox = grafo[u];
    grafo[u] = novo;
}

void dfs(int u) {
    if (ciclo) return;

    visitado[u] = 1; // visitando

    No* atual = grafo[u];
    while (atual != NULL) {
        int v = atual->valor;
        if (visitado[v] == 1) {
            ciclo = 1; // ciclo encontrado
            return;
        } else if (visitado[v] == 0) {
            dfs(v);
        }
        atual = atual->prox;
    }

    visitado[u] = 2; // terminado
}

void limpar_grafo() {
    for (int i = 1; i <= N; i++) {
        No* atual = grafo[i];
        while (atual) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
        grafo[i] = NULL;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int M;
        scanf("%d %d", &N, &M);

        memset(grafo, 0, sizeof(grafo));
        memset(visitado, 0, sizeof(visitado));
        ciclo = 0;

        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            inserir_aresta(A, B);
        }

        for (int i = 1; i <= N && !ciclo; i++) {
            if (!visitado[i])
                dfs(i);
        }

        printf(ciclo ? "SIM\n" : "NAO\n");

        limpar_grafo(); // liberar memória
    }

    return 0;
}
