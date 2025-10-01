#include <stdio.h>
#include <stdlib.h>

#define TAM 1005 // Tamanho máximo das estruturas

// Função para inserir na fila de prioridade (heap máximo)
void inserir_fila_prioridade(int fila[], int *tamanho, int valor) {
    fila[++(*tamanho)] = valor; // Insere o valor no final da fila
    int i = *tamanho;

    // Reorganiza os elementos para manter a propriedade de heap máximo
    while (i > 1 && fila[i / 2] < fila[i]) {
        int temp = fila[i];
        fila[i] = fila[i / 2];
        fila[i / 2] = temp;
        i /= 2;
    }
}

// Função para remover o maior elemento da fila de prioridade
int remover_fila_prioridade(int fila[], int *tamanho) {
    if (*tamanho == 0) return -1; // Fila vazia

    int maior = fila[1];
    fila[1] = fila[(*tamanho)--]; // Substitui a raiz pelo último elemento

    int i = 1;
    // Reorganiza a fila para manter a propriedade de heap máximo
    while (2 * i <= *tamanho) {
        int maior_filho = 2 * i;
        if (maior_filho + 1 <= *tamanho && fila[maior_filho + 1] > fila[maior_filho])
            maior_filho++;

        if (fila[i] >= fila[maior_filho]) break;

        int temp = fila[i];
        fila[i] = fila[maior_filho];
        fila[maior_filho] = temp;
        i = maior_filho;
    }

    return maior;
}

// Função para acessar o topo (maior elemento) da fila de prioridade
int topo_fila_prioridade(int fila[]) {
    return fila[1]; // O maior elemento sempre está na posição 1
}

int main() {
    int n;

    // Enquanto houver entrada (até EOF)
    while (scanf("%d", &n) != EOF) {
        // Declaração das estruturas
        int pilha[TAM];       // Para simular a estrutura de pilha
        int fila[TAM];        // Para simular a estrutura de fila comum
        int fila_prioridade[TAM]; // Para simular a fila de prioridade (máx-heap)

        // Ponteiros de controle
        int topo = -1;        // Para a pilha
        int inicio = 0, fim = 0; // Para a fila
        int tam_fp = 0;       // Para o tamanho da fila de prioridade

        // Flags para identificar quais estruturas ainda são possíveis
        int eh_pilha = 1;
        int eh_fila = 1;
        int eh_fila_prioridade = 1;

        // Loop de operações
        for (int i = 0; i < n; i++) {
            int operacao, valor;
            scanf("%d %d", &operacao, &valor);

            if (operacao == 1) {
                // Inserção nas três estruturas
                if (eh_pilha) pilha[++topo] = valor;
                if (eh_fila) fila[fim++] = valor;
                if (eh_fila_prioridade) inserir_fila_prioridade(fila_prioridade, &tam_fp, valor);
            } else if (operacao == 2) {
                // Remoção nas três estruturas

                // Pilha (LIFO)
                if (eh_pilha) {
                    if (topo < 0 || pilha[topo] != valor) {
                        eh_pilha = 0; // Valor não corresponde, então não é pilha
                    } else {
                        topo--;
                    }
                }

                // Fila (FIFO)
                if (eh_fila) {
                    if (inicio >= fim || fila[inicio] != valor) {
                        eh_fila = 0;
                    } else {
                        inicio++;
                    }
                }

                // Fila de prioridade
                if (eh_fila_prioridade) {
                    if (tam_fp == 0 || topo_fila_prioridade(fila_prioridade) != valor) {
                        eh_fila_prioridade = 0;
                    } else {
                        remover_fila_prioridade(fila_prioridade, &tam_fp);
                    }
                }
            }
        }

        // Verifica qual estrutura é válida
        int total = eh_pilha + eh_fila + eh_fila_prioridade;

        if (total == 0) {
            printf("impossible\n");
        } else if (total > 1) {
            printf("not sure\n");
        } else {
            if (eh_pilha) printf("stack\n");
            else if (eh_fila) printf("queue\n");
            else if (eh_fila_prioridade) printf("priority queue\n");
        }
    }

    return 0;
}

