#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore
typedef struct no {
    int altura;
    struct no *esq;
    struct no *dir;
} No;

// Função para criar um novo nó
No* criar_no(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->altura = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Função para inserir um valor na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criar_no(valor);
    }
    if (valor < raiz->altura) {
        raiz->esq = inserir(raiz->esq, valor);
    } else {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

// Percurso em-ordem (ordem crescente)
void in_ordem(No* raiz, int *primeiro) {
    if (raiz != NULL) {
        in_ordem(raiz->esq, primeiro);
        if (!(*primeiro)) printf(" ");
        printf("%d", raiz->altura);
        *primeiro = 0;
        in_ordem(raiz->dir, primeiro);
    }
}

// Função para liberar memória da árvore
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    int casos;
    scanf("%d", &casos);  // Número de cidades

    while (casos--) {
        int N;
        scanf("%d", &N);  // Número de pessoas na cidade

        No* raiz = NULL;

        for (int i = 0; i < N; i++) {
            int h;
            scanf("%d", &h);
            raiz = inserir(raiz, h);  // Insere cada altura na árvore
        }

        int primeiro = 1;
        in_ordem(raiz, &primeiro);  // Imprime em ordem crescente
        printf("\n");

        liberar(raiz);  // Libera a memória alocada
    }

    return 0;
}
