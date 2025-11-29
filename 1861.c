#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200003

// tabela hash de assassinos
typedef struct node {
    char name[16];
    int kills;
    struct node *next;
} Node;

Node *table[MAXN];

// hash simples (djb2)
unsigned long long djb2(const char *s) {
    unsigned long long h = 5381;
    int c;
    while ((c = *s++))
        h = ((h << 5) + h) + c;
    return h;
}

// marca mortos
typedef struct deadnode {
    char name[16];
    struct deadnode *next;
} DeadNode;

DeadNode *deadtable[MAXN];

int dead_exists(const char *s) {
    unsigned long long h = djb2(s) % MAXN;
    DeadNode *cur = deadtable[h];
    while (cur) {
        if (strcmp(cur->name, s) == 0) return 1;
        cur = cur->next;
    }
    return 0;
}

void dead_insert(const char *s) {
    unsigned long long h = djb2(s) % MAXN;
    DeadNode *n = malloc(sizeof(DeadNode));
    strcpy(n->name, s);
    n->next = deadtable[h];
    deadtable[h] = n;
}

Node* get_or_create(const char *s) {
    unsigned long long h = djb2(s) % MAXN;
    Node *cur = table[h];

    while (cur) {
        if (strcmp(cur->name, s) == 0) return cur;
        cur = cur->next;
    }

    Node *n = malloc(sizeof(Node));
    strcpy(n->name, s);
    n->kills = 0;
    n->next = table[h];
    table[h] = n;

    return n;
}

// vetor final para ordenação
typedef struct {
    char name[16];
    int kills;
} Out;

int cmp(const void *a, const void *b) {
    return strcmp(((Out*)a)->name, ((Out*)b)->name);
}

int main() {
    char killer[16], killed[16];

    while (scanf("%s %s", killer, killed) == 2) {

        // registra assassino
        Node *k = get_or_create(killer);
        k->kills++;

        // registra assassinado
        dead_insert(killed);
    }

    // coletar assassinos que não estão mortos
    Out arr[200005];
    int sz = 0;

    for (int i = 0; i < MAXN; i++) {
        Node *cur = table[i];
        while (cur) {
            if (!dead_exists(cur->name)) {
                strcpy(arr[sz].name, cur->name);
                arr[sz].kills = cur->kills;
                sz++;
            }
            cur = cur->next;
        }
    }

    // ordenar 
    qsort(arr, sz, sizeof(Out), cmp);

    // imprimir
    printf("HALL OF MURDERERS\n");
    for (int i = 0; i < sz; i++) {
        printf("%s %d\n", arr[i].name, arr[i].kills);
    }

    return 0;
}
