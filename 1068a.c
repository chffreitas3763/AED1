#include <stdio.h>
#include <string.h>

#define TAM 1000 // Tamanho máximo da expressão e da pilha

int main() {
    char expressao[TAM + 1]; // Vetor para armazenar a linha da expressão
    char pilha[TAM];         // Vetor para simular a pilha
    int topo;                // Representa o topo da pilha

    // Lê uma linha por vez até o final do arquivo (EOF)
    while (fgets(expressao, sizeof(expressao), stdin) != NULL) {
        topo = -1;          // Inicializa a pilha como vazia
        int correto = 1;    // Flag para indicar se a expressão está correta

        // Percorre cada caractere da expressão
        for (int i = 0; expressao[i] != '\0'; i++) {
            if (expressao[i] == '(') {
                // Empilha o parêntese
                pilha[++topo] = '(';
            } else if (expressao[i] == ')') {
                // Se a pilha estiver vazia, o parêntese está incorreto
                if (topo < 0) {
                    correto = 0;
                    break;
                } else {
                    // Desempilha
                    topo--;
                }
            }
        }

        // Se sobrou parênteses abertos na pilha, está incorreto
        if (topo >= 0) {
            correto = 0;
        }

        if (correto) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }

    return 0;
}
