/*************************************************************************
	> File Name: Trie.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月07日 星期二 16时25分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BASE 256
#define BL '0'

typedef struct Node {
    int flag;
    struct Node *next[BASE];
    char *str;
} Node, *Trie;

Node *get_new_node();
void clear(Trie);
Node *insert(Trie, const char *);
int search(Trie, const char *);
void get_random_string(char *);
void output(Trie, char *, int level);

int main() {
    Node *root = NULL;
    char str[256];
    for (int i = 0; ; i++) {
        printf("插入汉字: ");
        scanf("%s", str);
        if (str[0] == 'q') {
            printf("输入完成\n");
            break;
        }
        char *p = str;
        root = insert(root, p);
        printf("%s\n", str);
    }
    for (int i = 0; ; i++) {
        printf("查找汉字: ");
        scanf("%s", str);
        if (str[0] == 'q') {
            printf("查找完成\n");
            break;
        }
        char *p = str;
        int ret = search(root, p);
        printf(" = %d\n", ret);
    }
    
    
    return 0;
}

Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->str = (char *)malloc(3);
    return p;
}

void clear(Trie root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        clear(root->next[i]);
    }
    free(root);
    return ;
}

Node *insert(Trie root, const char *str) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        unsigned char ind = (unsigned char )str[i];
        if (p->next[ind] == NULL) p->next[ind] = get_new_node();
        p = p->next[ind];
    }
    p->flag = 1;

    return root;
}

int search(Trie root, const char *str) {
    Node *p = root;
    int i = 0;
    while (p->next[(unsigned char)str[i]] && str[i]) {
        if (p->next[(unsigned char)str[i]])
            p = p->next[(unsigned char) str[i++]];
    }
    return (p && p->flag);
}

void get_random_string(char *str) {
    int len = rand() % 10;
    for (int i = 0; i < len; i++) {
        str[i] = BL + rand() % BASE;
    }
    str[len] = 0;
    return ;
}

void output(Trie root, char *str, int level) {
    if (root == NULL) return ;
    str[level] = 0;
    if (root->flag) printf("find word : %s\n", root->str);
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        str[level] = i + BL;
        output(root->next[i], str, level + 1);
    }
    return ;
}
