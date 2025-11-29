#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left, *right;
} Node;

Node* insert(Node *root, int x) {
    if (root == NULL) {
        Node *n = (Node*)malloc(sizeof(Node));
        n->val = x;
        n->left = n->right = NULL;
        return n;
    }
    if (x < root->val)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);
    return root;
}

typedef struct {
    Node *data[600];  // N <= 500
    int front, back;
} Queue;

void q_init(Queue *q) {
    q->front = q->back = 0;
}

int q_empty(Queue *q) {
    return q->front == q->back;
}

void q_push(Queue *q, Node *x) {
    q->data[q->back++] = x;
}

Node* q_pop(Queue *q) {
    return q->data[q->front++];
}

int main() {
    int C;
    scanf("%d", &C);

    for (int cs = 1; cs <= C; cs++) {
        int N;
        scanf("%d", &N);

        Node *root = NULL;

        for (int i = 0; i < N; i++) {
            int x; 
            scanf("%d", &x);
            root = insert(root, x);
        }

        // BFS (percurso por nível)
        Queue q;
        q_init(&q);
        q_push(&q, root);

        printf("Case %d:\n", cs);

        int first = 1;
        while (!q_empty(&q)) {
            Node *u = q_pop(&q);

            if (first) {
                printf("%d", u->val);
                first = 0;
            } else {
                printf(" %d", u->val);
            }

            if (u->left)  q_push(&q, u->left);
            if (u->right) q_push(&q, u->right);
        }

        printf("\n\n"); 
    }

    return 0;
}
