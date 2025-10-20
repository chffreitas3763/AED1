#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da fila
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Função para enfileirar (inserir no fim)
void enfileirar(No** inicio, No** fim, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = NULL;

    if (*fim != NULL) {
        (*fim)->proximo = novo;
    } else {
        *inicio = novo; // Primeiro elemento
    }

    *fim = novo; // Atualiza o fim
}

// Função para desenfileirar (remover do início)
int desenfileirar(No** inicio, No** fim) {
    if (*inicio == NULL) return -1; // Fila vazia

    No* temp = *inicio;
    int valor = temp->valor;
    *inicio = temp->proximo;

    if (*inicio == NULL) {
        *fim = NULL; // A fila ficou vazia
    }

    free(temp);
    return valor;
}

// Função para liberar memória da fila (boa prática)
void liberar_fila(No** inicio) {
    No* atual = *inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *inicio = NULL;
}

int main() {
    int n;

    while (scanf("%d", &n), n != 0) {
        No* inicio = NULL; // Início da fila
        No* fim = NULL;    // Fim da fila

        // Preenche a fila com as cartas de 1 até n
        for (int i = 1; i <= n; i++) {
            enfileirar(&inicio, &fim, i);
        }

        printf("Discarded cards:");

        // Processa as jogadas até restar apenas 1 carta
        int primeira = 1;
        while (inicio != fim) {
            // 1. Remove e imprime a carta descartada
            int descartada = desenfileirar(&inicio, &fim);
            if (primeira) {
                printf(" %d", descartada);
                primeira = 0;
            } else {
                printf(", %d", descartada);
            }

            // 2. Move a próxima carta para o final da fila
            int proxima = desenfileirar(&inicio, &fim);
            enfileirar(&inicio, &fim, proxima);
        }

        // Carta restante
        printf("\nRemaining card: %d\n", inicio->valor);

        liberar_fila(&inicio); // Libera memória
    }

    return 0;
}
