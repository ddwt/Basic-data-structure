/*************************************************************************
	> File Name: 6.binary_tree2.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月01日 星期三 11时05分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define malloc2(size) (my_malloc(size, __FILE__, __func__, __LINE__))

void *my_malloc(int size, const char *file, const char *func, const char line) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "%s : %s -> %s malloc error\n", file, func, line);
        exit(0);
    }
    return ;
}

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Queue {
    Node **data;
    int size, front, tail;
    int count;
} Queue;

Queue *qinit(int);
void qclear(Queue *);
Node *qfront(Queue *);
int qpush(Queue *, Node *);
int qpop(Queue *);
int qempty(Queue *);

Node *init(char);
void clear(Node *);
void levelorder(Node *);
Node *build(char *);


int main() {
    char str[100] = {0};
    scanf("%s", str);
    if (strlen(str) == 0) return 0;
    Node *root = build(str);
    levelorder(root);
    return 0;
}

Node *init(char data) {
    Node *node = (Node *)malloc2(sizeof(Node));
    node->data = data;
    node->lchild = node->rchild = NULL;
    return node;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void levelorder(Node *root) {
    Queue *q = qinit(100);
    qpush(q, root);
    while (qempty(q) != 1) {
        Node *p = qfront(q);
        printf("%c ", p->data);
        qpop(q);
        if (p->lchild != NULL) qpush(q, p->lchild);
        if (p->rchild != NULL) qpush(q, p->rchild);
    }
}

Node *build(char *str) {
    Node **tree = (Node **)malloc2(sizeof(Node *) * 100);
    Node *p = NULL, *root = NULL;
    int top = -1, flag = 2;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '(':
                tree[++top] = p;
                flag = 0;
                break;
            case ',':
                flag = 1;
                break;
            case ')':
                top--;
                break;
            default :
                p = init(str[i]);
                if (root == NULL) {
                    root = p;
                } else {
                    switch (flag) {
                        case 0:
                            tree[top]->lchild = p;
                            break;
                        case 1:
                            tree[top]->rchild = p;
                            break;
                        default:
                            break;
                    }
                } 
                break;
        }
    }
    return root;
}

Queue *qinit(int n) {
    Queue *q = (Queue *)malloc2(sizeof(Queue *));
    q->data = (Node **)malloc2(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        q->data[i] = (Node *)malloc2(sizeof(Node));
    }
    q->size = n;
    q->front = 0;
    q->tail = -1;
    q->count = 0;
    return q;
}

void qclear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

Node *qfront(Queue *q) {
    return q->data[q->front];
}

int qpush(Queue *q, Node *node) {
    if (q->count == q->size) return 0;
    q->tail = (q->tail + 1) % q->size;
    q->data[q->tail] = node;
    q->count += 1;
    return 1;
}

int qpop(Queue *q) {
    if (qempty(q)) return 0;
    q->front = (q->front + 1) % q->size;
    q->count -= 1;
    return 1;
}

int qempty(Queue *q) {
    return q->count == 0;
}

