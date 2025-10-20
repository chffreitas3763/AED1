#include <stdio.h>
#include <stdlib.h>

#define MAX_PESSOAS 3000000

// Função que mescla (intercala) dois subvetores ordenados
void mesclar(int vetor[], int inicio, int meio, int fim) {
    int tamanho_esquerda = meio - inicio + 1;
    int tamanho_direita = fim - meio;

    // Vetores temporários
    int *esquerda = (int *)malloc(tamanho_esquerda * sizeof(int));
    int *direita = (int *)malloc(tamanho_direita * sizeof(int));

    // Copia os elementos para os vetores temporários
    for (int i = 0; i < tamanho_esquerda; i++) {
        esquerda[i] = vetor[inicio + i];
    }

    for (int j = 0; j < tamanho_direita; j++) {
        direita[j] = vetor[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;

    // Mescla os dois vetores ordenadamente de volta para o vetor original
    while (i < tamanho_esquerda && j < tamanho_direita) {
        if (esquerda[i] <= direita[j]) {
            vetor[k++] = esquerda[i++];
        } else {
            vetor[k++] = direita[j++];
        }
    }

    // Copia os elementos restantes (se houver)
    while (i < tamanho_esquerda) {
        vetor[k++] = esquerda[i++];
    }

    while (j < tamanho_direita) {
        vetor[k++] = direita[j++];
    }

    // Libera a memória dos vetores temporários
    free(esquerda);
    free(direita);
}

// Função recursiva do Merge Sort
void mergesort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergesort(vetor, inicio, meio);       // Ordena a metade esquerda
        mergesort(vetor, meio + 1, fim);      // Ordena a metade direita
        mesclar(vetor, inicio, meio, fim);    // Mescla as duas metades
    }
}

int main() {
    int quantidade_de_casos;
    scanf("%d", &quantidade_de_casos);

    for (int caso = 0; caso < quantidade_de_casos; caso++) {
        int quantidade_de_pessoas;
        scanf("%d", &quantidade_de_pessoas);

        int alturas[MAX_PESSOAS];

        // Leitura das alturas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            scanf("%d", &alturas[i]);
        }

        // Ordena com Merge Sort
        mergesort(alturas, 0, quantidade_de_pessoas - 1);

        // Imprime as alturas ordenadas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            if (i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");
    }

    return 0;
}
