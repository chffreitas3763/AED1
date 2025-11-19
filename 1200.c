#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó da árvore
typedef struct No {
    char valor;
    struct No *esq, *dir;
} No;

// Cria um novo nó com valor
No* criar_no(char valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

// Insere um caractere na ABP
No* inserir(No* raiz, char valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

// Pesquisa se um caractere existe
int buscar(No* raiz, char valor) {
    if (raiz == NULL) return 0;
    if (valor == raiz->valor) return 1;
    if (valor < raiz->valor) return buscar(raiz->esq, valor);
    else return buscar(raiz->dir, valor);
}

// Impressões com controle de espaço
void infixa(No* raiz, int* primeiro) {
    if (raiz) {
        infixa(raiz->esq, primeiro);
        if (!(*primeiro)) printf(" ");
        printf("%c", raiz->valor);
        *primeiro = 0;
        infixa(raiz->dir, primeiro);
    }
}

void prefixa(No* raiz, int* primeiro) {
    if (raiz) {
        if (!(*primeiro)) printf(" ");
        printf("%c", raiz->valor);
        *primeiro = 0;
        prefixa(raiz->esq, primeiro);
        prefixa(raiz->dir, primeiro);
    }
}

void posfixa(No* raiz, int* primeiro) {
    if (raiz) {
        posfixa(raiz->esq, primeiro);
        posfixa(raiz->dir, primeiro);
        if (!(*primeiro)) printf(" ");
        printf("%c", raiz->valor);
        *primeiro = 0;
    }
}

// Libera memória da árvore
void liberar(No* raiz) {
    if (raiz) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}

int main() {
    char comando[20], letra;
    No* raiz = NULL;

    while (scanf("%s", comando) != EOF) {
        if (strcmp(comando, "I") == 0) {
            scanf(" %c", &letra);
            raiz = inserir(raiz, letra);
        }
        else if (strcmp(comando, "P") == 0) {
            scanf(" %c", &letra);
            if (buscar(raiz, letra))
                printf("%c existe\n", letra);
            else
                printf("%c nao existe\n", letra);
        }
        else if (strcmp(comando, "INFIXA") == 0) {
            int primeiro = 1;
            infixa(raiz, &primeiro);
            printf("\n");
        }
        else if (strcmp(comando, "PREFIXA") == 0) {
            int primeiro = 1;
            prefixa(raiz, &primeiro);
            printf("\n");
        }
        else if (strcmp(comando, "POSFIXA") == 0) {
            int primeiro = 1;
            posfixa(raiz, &primeiro);
            printf("\n");
        }
    }

    liberar(raiz); // Libera memória ao final
    return 0;
}
