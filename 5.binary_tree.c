/*************************************************************************
	> File Name: 5.binary_tree.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 19时28分37秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define malloc2(size) (my_malloc(size, __FILE__, __func__, __LINE__))

#define DEFAULTARG(n, x) (#n[0] ? n + 0 : x)
#define getNode(n) (__getNode(DEFAULTARG(n , 10)))

void *my_malloc(int size, const char *file, const char *func, const char *line) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf("%s -> %s : %s malloc error\n", file, func, line);
        fflush(stderr);
        exit(-1);
    }
    return data;
}

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *__getNode(int);
void clear(Node *);
void preorder(Node *);
void inorder(Node *);
void postorder(Node *);

int main() {
    Node *root = getNode(1);
    root->lchild = getNode(2);
    root->rchild = getNode(3);
    root->lchild->lchild = getNode(7);
    root->lchild->rchild = getNode(8);
    root->lchild->rchild->lchild = getNode(9);
    root->rchild->rchild = getNode(4);
    root->rchild->rchild->lchild = getNode(5);
    root->rchild->rchild->rchild = getNode(6);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    return 0;
}

Node *__getNode(int key) {
    Node *p = (Node *)malloc2(sizeof(Node));    
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void preorder(Node *root) {
    if (root == NULL) return ;
    printf("%d ", root->key);
    preorder(root->rchild);
    preorder(root->lchild);
    return ;
}

void inorder(Node *root) {
    if (root == NULL) return ;
    inorder(root->lchild);
    printf("%d ", root->key);
    inorder(root->rchild);
    return ;
}

void postorder(Node *root) {
    if (root == NULL) return ;
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d ", root->key);
    return ;
}
