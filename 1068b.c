#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do nó da lista encadeada (pilha dinâmica)
typedef struct No {
    char dado;           // Aqui guardaremos sempre '('
    struct No* prox;     // Aponta para o próximo nó
} No;

// Função para empilhar (push)
void empilhar(No** topo, char valor) {
    No* novo = (No*)malloc(sizeof(No)); // Aloca memória para um novo nó
    novo->dado = valor;
    novo->prox = *topo; // O próximo do novo nó será o antigo topo
    *topo = novo;       // Atualiza o topo para o novo nó
}

// Função para desempilhar (pop)
int desempilhar(No** topo) {
    if (*topo == NULL) { // Se a pilha estiver vazia
        return 0;        // Retorna 0 para indicar erro
    }
    No* temp = *topo;
    *topo = (*topo)->prox; // Avança o topo para o próximo nó
    free(temp);            // Libera o nó removido
    return 1;              // Retorna 1 para indicar sucesso
}

// Função para verificar se a pilha está vazia
int pilha_vazia(No* topo) {
    return (topo == NULL);
}

// Função para liberar toda a pilha (boa prática)
void liberar_pilha(No** topo) {
    while (*topo != NULL) {
        No* temp = *topo;
        *topo = (*topo)->prox;
        free(temp);
    }
}

int main() {
    char expressao[1001]; // Para armazenar cada linha
    No* topo = NULL;      // Ponteiro para o topo da pilha

    // Lê até o EOF
    while (fgets(expressao, sizeof(expressao), stdin) != NULL) {
        topo = NULL;         // Inicia a pilha vazia para cada expressão
        int correto = 1;     // Assume correto até encontrar erro

        // Percorre a string
        for (int i = 0; expressao[i] != '\0'; i++) {
            if (expressao[i] == '(') {
                empilhar(&topo, '('); // Empilha cada parêntese aberto
            } else if (expressao[i] == ')') {
                // Tenta desempilhar. Se falhar, é erro.
                if (!desempilhar(&topo)) {
                    correto = 0;
                    break;
                }
            }
        }

        // Se ainda houver parênteses abertos na pilha, está incorreto
        if (!pilha_vazia(topo)) {
            correto = 0;
        }

        // Libera a pilha usada nesta linha
        liberar_pilha(&topo);

        // Imprime o resultado
        if (correto) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }

    return 0;
}
