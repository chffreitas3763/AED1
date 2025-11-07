#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

// Função para criar um novo nó
No* criar_no(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Função para inserir um valor na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL)
        return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

// Percurso pré-ordem: raiz -> esquerda -> direita
void pre_ordem(No* raiz, int* primeiro) {
    if (raiz != NULL) {
        if (!(*primeiro)) printf(" ");
        printf("%d", raiz->valor);
        *primeiro = 0;
        pre_ordem(raiz->esq, primeiro);
        pre_ordem(raiz->dir, primeiro);
    }
}

// Percurso em ordem: esquerda -> raiz -> direita
void em_ordem(No* raiz, int* primeiro) {
    if (raiz != NULL) {
        em_ordem(raiz->esq, primeiro);
        if (!(*primeiro)) printf(" ");
        printf("%d", raiz->valor);
        *primeiro = 0;
        em_ordem(raiz->dir, primeiro);
    }
}

// Percurso pós-ordem: esquerda -> direita -> raiz
void pos_ordem(No* raiz, int* primeiro) {
    if (raiz != NULL) {
        pos_ordem(raiz->esq, primeiro);
        pos_ordem(raiz->dir, primeiro);
        if (!(*primeiro)) printf(" ");
        printf("%d", raiz->valor);
        *primeiro = 0;
    }
}

// Libera memória da árvore
void liberar(No* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    int casos;
    scanf("%d", &casos);

    for (int c = 1; c <= casos; c++) {
        int n;
        scanf("%d", &n);

        No* raiz = NULL;

        // Inserção dos valores na árvore
        for (int i = 0; i < n; i++) {
            int valor;
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        printf("Case %d:\n", c);

        int primeiro = 1;
        printf("Pre.: ");
        pre_ordem(raiz, &primeiro);

        primeiro = 1;
        printf("\nIn..: ");
        em_ordem(raiz, &primeiro);

        primeiro = 1;
        printf("\nPost: ");
        pos_ordem(raiz, &primeiro);

        printf("\n\n");

        liberar(raiz);
    }

    return 0;
}
