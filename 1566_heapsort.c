#include <stdio.h>

#define MAX_PESSOAS 3000000

// Função para trocar dois valores
void trocar(int *a, int *b) {
    int temporario = *a;
    *a = *b;
    *b = temporario;
}

// Função para "reajustar" o heap (heapify)
void ajustar_heap(int vetor[], int tamanho, int indice_raiz) {
    int maior = indice_raiz;
    int esquerda = 2 * indice_raiz + 1;
    int direita = 2 * indice_raiz + 2;

    // Compara com o filho da esquerda
    if (esquerda < tamanho && vetor[esquerda] > vetor[maior]) {
        maior = esquerda;
    }

    // Compara com o filho da direita
    if (direita < tamanho && vetor[direita] > vetor[maior]) {
        maior = direita;
    }

    // Se a raiz não é o maior, troca e continua ajustando
    if (maior != indice_raiz) {
        trocar(&vetor[indice_raiz], &vetor[maior]);
        ajustar_heap(vetor, tamanho, maior);
    }
}

// Função principal do HeapSort
void heapsort(int vetor[], int tamanho) {
    // 1. Constrói o heap máximo (reorganiza o vetor)
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        ajustar_heap(vetor, tamanho, i);
    }

    // 2. Extrai os elementos do heap um por um
    for (int i = tamanho - 1; i >= 0; i--) {
        trocar(&vetor[0], &vetor[i]);         // Move o maior para o fim
        ajustar_heap(vetor, i, 0);            // Reajusta o heap
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

        // Ordena com HeapSort
        heapsort(alturas, quantidade_de_pessoas);

        // Imprime as alturas ordenadas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            if (i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");
    }

    return 0;
}
