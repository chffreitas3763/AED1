#include <stdio.h>

#define MAX_PESSOAS 3000000

// Função para ordenar o vetor usando o método de inserção
void ordenar_por_insercao(int vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int atual = vetor[i];
        int j = i - 1;

        // Move os elementos maiores para frente
        while (j >= 0 && vetor[j] > atual) {
            vetor[j + 1] = vetor[j];
            j--;
        }

        // Insere o valor atual na posição correta
        vetor[j + 1] = atual;
    }
}

int main() {
    int quantidade_de_casos;
    scanf("%d", &quantidade_de_casos); // Lê o número de cidades

    // Repetição para cada cidade
    for (int caso = 0; caso < quantidade_de_casos; caso++) {
        int quantidade_de_pessoas;
        scanf("%d", &quantidade_de_pessoas); // Lê o número de pessoas na cidade

        // Cria um vetor para armazenar as alturas
        int alturas[MAX_PESSOAS];

        // Lê todas as alturas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            scanf("%d", &alturas[i]);
        }

        // Ordena as alturas com o método de inserção
        ordenar_por_insercao(alturas, quantidade_de_pessoas);

        // Imprime as alturas ordenadas
        for (int i = 0; i < quantidade_de_pessoas; i++) {
            if (i > 0) printf(" ");
            printf("%d", alturas[i]);
        }
        printf("\n"); // Quebra de linha entre os casos
    }

    return 0;
}
