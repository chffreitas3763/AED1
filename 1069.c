#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da lista encadeada (simula a pilha)
typedef struct No {
    char simbolo;
    struct No* proximo;
} No;

// Função para empilhar (adiciona um novo '<' na pilha)
void empilhar(No** topo, char simbolo) {
    No* novo = (No*)malloc(sizeof(No));
    novo->simbolo = simbolo;
    novo->proximo = *topo;
    *topo = novo;
}

// Função para desempilhar (remove o topo da pilha, se existir)
int desempilhar(No** topo) {
    if (*topo == NULL) {
        return 0; // pilha vazia
    }
    No* temp = *topo;
    *topo = (*topo)->proximo;
    free(temp);
    return 1;
}

// Função para liberar toda a memória da pilha ao final de cada linha
void liberar_pilha(No** topo) {
    while (*topo != NULL) {
        No* temp = *topo;
        *topo = (*topo)->proximo;
        free(temp);
    }
}

int main() {
    int quantidade_de_testes;
    char linha[1001]; // Cada linha tem até 1000 caracteres (+1 para o \0)

    // Lê o número de casos de teste
    scanf("%d", &quantidade_de_testes);
    getchar(); // Consome o ENTER após o número

    // Processa cada linha
    for (int caso = 0; caso < quantidade_de_testes; caso++) {
        fgets(linha, sizeof(linha), stdin); // Lê uma linha da entrada

        No* pilha = NULL; // Inicializa a pilha vazia
        int quantidade_de_diamantes = 0;

        // Percorre caractere por caractere
        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] == '<') {
                empilhar(&pilha, '<'); // Empilha
            } else if (linha[i] == '>') {
                if (desempilhar(&pilha)) { // Só desempilha se houver '<'
                    quantidade_de_diamantes++;
                }
            }
            // Ignora os pontos '.' e outros símbolos
        }

        // Libera a memória da pilha (boa prática)
        liberar_pilha(&pilha);

        // Imprime a quantidade de diamantes extraídos
        printf("%d\n", quantidade_de_diamantes);
    }

    return 0;
}
