#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 200003  // número de buckets na hash (primo grande)

// estrutura para encadeamento
typedef struct node {
    unsigned long long h;
    struct node *next;
} Node;

Node *table[MAXN];

// hash djb2 (rápida e boa para strings curtas)
unsigned long long hash_djb2(const char *str) {
    unsigned long long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + (unsigned long long)c;
    return h;
}

int main() {
    char s[1000005];
    int count = 0;

    for (int i = 0; i < MAXN; i++) table[i] = NULL;

    while (scanf("%s", s) != EOF) {
        unsigned long long h = hash_djb2(s);
        int b = h % MAXN;

        Node *cur = table[b];
        int found = 0;

        // verifica se já existe
        while (cur) {
            if (cur->h == h) { 
                found = 1;
                break;
            }
            cur = cur->next;
        }

        if (!found) {
            // inserir
            Node *n = malloc(sizeof(Node));
            n->h = h;
            n->next = table[b];
            table[b] = n;
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}
