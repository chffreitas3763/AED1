#include <stdio.h>

#define MAX_PESSOAS 3000000

// Função para trocar dois valores
void trocar(int *a, int *b) {
    int temporario = *a;
    *a = *b;
    *b = temporario;
}

// Função de ordenação por seleção (Selection Sort)
void ordenar_por_selecao(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int menor_posicao = i;

        // Encontra a posição do menor elemento restante
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[menor_posicao]) {
                menor_posicao = j;
            }
        }

        // Troca o menor com o elemento atual
        if (menor_posicao != i) {
            trocar(&vetor[i], &vetor[menor_posicao]);
        }
    }
}

int main() {
    int quantidade_de_casos;
    scanf("%d", &quantidade_de_casos);

    for (int caso = 0; caso < quantidade_de_casos; caso++) {
        int quantidade_de_pessoas;
        scanf("%d", &quantidade_de_pessoas);

        // Vetor para armazenar as alturas
        int alturas[MAX_PESSOAS];

        // Leitura das alturas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            scanf("%d", &alturas[i]);
        }

        // Ordena usando Selection Sort
        ordenar_por_selecao(alturas, quantidade_de_pessoas);

        // Impressão das alturas ordenadas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            if (i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n");
    }

    return 0;
}
