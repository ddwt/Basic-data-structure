#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int flag;
    struct Node *next[2];
} Node, *Trie;

int num[256][8] = {0};
int node_cnt = 0;

void get_num(int (*num)[8]) {
    for (int i = 0; i < 256; i++) {
        int temp = i;
        for (int j = 0; j < 8; j++) {
            num[i][j] = temp % 2;
            temp /= 2;
        }
    }
}

Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    node_cnt += 1;
    return p;
}

Node *insert(Trie root, int *num, int len) {
    if(!root) root = get_new_node(); 
    Node *p = root;
    for (int i = 0; i < len; i++) {
        if (p->next[num[i]] == NULL) p->next[num[i]] = get_new_node();
        p = p->next[num[i]];
    }
    p->flag = 1;
    return root;
}
Node *insert2(Trie root, unsigned char *str) {
    if(!root) root = get_new_node(); 
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < 8; j++) {
            if (p->next[num[str[i]][j]] == NULL) p->next[num[str[i]][j]] = get_new_node();
            p = p->next[num[str[i]][j]];
        }
    }
    p->flag = 1;
    return root;
}

int search(Trie root, int *num, int len) { 
    Node *p = root;
    for (int i = 0; i < len; i++) {
        if (p->next[num[i]] == NULL) {
            return 0;
        }
        p = p->next[num[i]];
    }
    return 1;
}

int search2(Trie root, unsigned char *str) { 
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        for (int j = 0; j < 8; j++) {
            if (p->next[num[str[i]][j]] == NULL) return 0;
            p = p->next[num[str[i]][j]];
        }
    }
    return 1;
}
int *str_to_num(unsigned char *str) {
    int *num = (int *)calloc(sizeof(int), strlen(str) * 8 + 5);
    int ind = 0;
    int n = 0;
    for (int i = 0; str[i]; i++) {
        for (int i = 0; i < 8; i++) {
            num[ind++] = str[i] % 2;
            str[i] /= 2;
        }
    }
    return num;
}

int main() {
    int word_cnt = 0;
    double percent = 0;
    get_num(num);
    Node *root = NULL;
    unsigned char str[1000];
    int n;
    printf("插入字符串个数");
    scanf("%d", &n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        //int *num = str_to_num(str);
        word_cnt += strlen(str);
        //int len = strlen(str) * 8;
        //root = insert(root, num, len);
        root = insert2(root, str);
    }
    percent =(double) word_cnt / node_cnt / sizeof(Node);
    printf("输入完成，存储效率 = %lf\n", percent);
    while (1) {
        scanf("%s", str);
        if (strcmp(str, "quit") == 0) break;
        //int *num = str_to_num(str);
        //int len = strlen(str) * 8;
        //int ret = search(root, num, len);
        int ret = search2(root, str);
        printf("ret = %d\n",ret);
    }

    return 0;
}
