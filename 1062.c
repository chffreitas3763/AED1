#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Estrutura de pilha simples
typedef struct {
    int dados[MAX];
    int topo;
} Pilha;

// Inicializa a pilha
void inicializar(Pilha* p) {
    p->topo = -1;
}

// Verifica se está vazia
int vazia(Pilha* p) {
    return p->topo == -1;
}

// Empilha um elemento
void empilhar(Pilha* p, int valor) {
    p->dados[++(p->topo)] = valor;
}

// Desempilha um elemento
int desempilhar(Pilha* p) {
    return p->dados[(p->topo)--];
}

// Retorna o topo da pilha
int topo(Pilha* p) {
    return p->dados[p->topo];
}

// Função para verificar se a sequência desejada é possível
int pode_formar_sequencia(int n, int saida[]) {
    Pilha pilha;
    inicializar(&pilha);

    int proximo_trem = 1;  // trem que chega
    int indice_saida = 0;  // posição atual da sequência de saída

    while (proximo_trem <= n) {
        empilhar(&pilha, proximo_trem);

        // Desempilha enquanto o topo da pilha for igual à saída esperada
        while (!vazia(&pilha) && topo(&pilha) == saida[indice_saida]) {
            desempilhar(&pilha);
            indice_saida++;
        }

        proximo_trem++;
    }

    // Se conseguimos formar toda a sequência, deu certo
    return indice_saida == n;
}

int main() {
    int n;

    while (scanf("%d", &n) && n != 0) {
        while (1) {
            int primeira_entrada;
            scanf("%d", &primeira_entrada);

            if (primeira_entrada == 0) {
                printf("\n"); // fim dos testes para esse valor de n
                break;
            }

            int saida[MAX];
            saida[0] = primeira_entrada;

            // Lê os demais valores da sequência
            for (int i = 1; i < n; i++) {
                scanf("%d", &saida[i]);
            }

            // Verifica se é possível formar a sequência com a pilha
            if (pode_formar_sequencia(n, saida)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }

    return 0;
}
