#include <stdio.h>

#define MAX_PESSOAS 3000000

// Função para trocar dois valores de posição
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função que particiona o vetor para o QuickSort
int particionar(int vetor[], int esquerda, int direita) {
    int pivo = vetor[direita]; // Escolhe o último elemento como pivô
    int i = esquerda - 1;

    for (int j = esquerda; j < direita; j++) {
        if (vetor[j] <= pivo) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }

    trocar(&vetor[i + 1], &vetor[direita]);
    return i + 1; // Retorna a posição correta do pivô
}

// Função principal do QuickSort (recursiva)
void quicksort(int vetor[], int esquerda, int direita) {
    if (esquerda < direita) {
        int indice_pivo = particionar(vetor, esquerda, direita);
        quicksort(vetor, esquerda, indice_pivo - 1);
        quicksort(vetor, indice_pivo + 1, direita);
    }
}

int main() {
    int quantidade_de_casos;
    scanf("%d", &quantidade_de_casos); // Lê o número de cidades

    for (int caso = 0; caso < quantidade_de_casos; caso++) {
        int quantidade_de_pessoas;
        scanf("%d", &quantidade_de_pessoas);

        int alturas[MAX_PESSOAS];

        // Lê as alturas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            scanf("%d", &alturas[i]);
        }

        // Ordena com quicksort
        quicksort(alturas, 0, quantidade_de_pessoas - 1);

        // Imprime as alturas ordenadas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            if (i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");
    }

    return 0;
}
