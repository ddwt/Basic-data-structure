#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256
#define MAX_N 10000

#define swap(a, b) { \
    __typeof(a) temp = a; \
    a = b; b = temp; \
}

int word_cnt[SIZE] = {0};

typedef struct Node {
    //int cnt;
    int flag;
    struct Node *next[2];
} Node, *Trie;

typedef struct HFNode {
    unsigned char ch;
    int frep;
    struct HFNode *lchild, *rchild;
} HFNode;

typedef struct Heap {
    HFNode **data;
    int count, size;
} Heap;

Heap *init(int);
int push(Heap *, HFNode *);
int pop(Heap *);
int empty(Heap *);
HFNode *top(Heap *);

Node *get_new_node();
Node *insert(Trie , unsigned char *, unsigned char huff_code[SIZE][SIZE]);
int search(Trie, unsigned char *, unsigned char huff_code[SIZE][SIZE]);

HFNode *get_hf_node(unsigned char, int);
HFNode *build(Heap *);
void extract(HFNode *, unsigned char *buff, unsigned char (*)[SIZE], int);

void get_words1(int *word_cnt) {
    unsigned char str[MAX_N];
    while (1) {
        scanf("%s", str);
        if (strcmp(str, "quit") == 0) return ;
        for (int i = 0; str[i]; i++) {
            word_cnt[str[i]]++;
        }
    }
}

int node_cnt = 0;

int main() {
    Heap *h = init(SIZE);
    //统计词频
    int word_cnt[SIZE] = {0};
    get_words1(word_cnt);

    //建堆(哈夫曼节点)
    for (int i = 0; i < SIZE; i++) {
        if (word_cnt[i]) {
            HFNode *temp = get_hf_node(i, word_cnt[i]);
            int ret = push(h, temp);
        }
    }
    //构建哈夫曼树并编码
    //printf("h->count = %d\n", h->count);
    HFNode *root = build(h);
    if (root->lchild == NULL) printf("nulli\n");
    if (root->rchild == NULL) printf("nulli\n");
    //printf("建树完成\n");
    unsigned char huffman_code[SIZE][SIZE] = {0};
    unsigned char buff[SIZE] = {0};
    extract(root, buff, huffman_code, 0);
    /*
    for (int i = 0; i < 256; i++) {
        if (huffman_code[i][0] == 0) continue;
        printf("%d : %s\n", i, huffman_code[i]);
    }
    */
    //构建字典树
    double percent;
    int str_cnt = 0;
    Node *trie = NULL;
    printf("插入字符串数量:\n");
    int n;
    scanf("%d", &n);
    char str[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        trie = insert(trie, str, huffman_code);
        str_cnt += strlen(str);
    }
    //printf("str_cnt = %d\n node_cnt = %d\n, sizeof(Node) = %d\n", str_cnt, node_cnt, sizeof(Node));
    percent = (double) str_cnt / node_cnt / sizeof(Node);
    printf("输入完成，存储效率 = %lf\n", percent);
    while (1) {
        scanf("%s", str);
        if (strcmp(str, "quit") == 0) break;
        int ret = search(trie, str, huffman_code);
        printf("ret = %d\n", ret);
    }
    
    return 0;
}

Heap *init(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (HFNode **)calloc(sizeof(HFNode *), n);
    h->size = n;
    h->count = 0;
    return h;
}

int push(Heap *h, HFNode *node) {
    if (h->count >= h->size) return 0;
    h->count += 1;
    h->data[h->count] = node;
    int ind = h->count;
    while (ind > 1) {
        if (h->data[ind >> 1]->frep <= h->data[ind]->frep)  break;
        HFNode *temp = h->data[ind >> 1];
        h->data[ind >> 1] = h->data[ind];
        h->data[ind] = temp;
        ind >>= 1;
    }
    return 1;
}

int pop(Heap *h) {
    if (h->count <= 1) {
        h->count = 0;
        return 0;
    }
    HFNode *temp = h->data[1];
    h->data[1] = h->data[h->count];
    h->data[h->count] = temp;
    h->count -= 1;
    int ind = 1;
    while (ind * 2 <= h->count) {
        int min_ind = ind;
        if (h->data[ind << 1]->frep < h->data[min_ind]->frep) min_ind = ind << 1;
        if ((ind << 1 | 1) <= h->count && h->data[ind << 1 | 1]->frep < h->data[min_ind]->frep) min_ind = ind << 1 | 1;
        if (min_ind == ind) break;
        HFNode *temp = h->data[min_ind];
        h->data[min_ind] = h->data[ind];
        h->data[ind] = temp;
        ind = min_ind;
    }
    return 1;
}

int empty(Heap *h) {
    return h->count == 0;
}

HFNode *top(Heap *h) {
    if (h->count == 0) {
        return NULL;
    }
    return h->data[1];
}

Node *get_new_node() {
    node_cnt += 1;
    return (Node *)calloc(sizeof(Node), 1);
}

Node *insert(Trie root, unsigned char *str, unsigned char (*huffman_code)[SIZE]) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        for (int j = 0; huffman_code[str[i]][j]; j++) {
            int ind = huffman_code[str[i]][j] - '0';
            if (p->next[ind] == NULL) {
                p->next[ind] = get_new_node();
            }
            p = p->next[ind];
        }
    }
    p->flag = 1;
    return root;
}

int search(Trie root, unsigned char *str, unsigned char huffman_code[SIZE][SIZE]) {
    if (root == NULL) return 0;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        for (int j = 0; huffman_code[str[i]][j]; j++) {
            if (p->next[huffman_code[str[i]][j] - '0'] == NULL) return 0;
            p = p->next[huffman_code[str[i]][j] - '0'];
        }
    }
    return p->flag;
}

HFNode *get_hf_node(unsigned char ch, int frep) {
    HFNode *p = (HFNode *)malloc(sizeof(HFNode));
    p->ch = ch;
    p->frep = frep;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

HFNode *build(Heap *h) {
    while (h->count > 1) {
        HFNode *l = top(h);
        pop(h);
        HFNode *r = top(h);
        pop(h);
        HFNode *new_node = get_hf_node('q', l->frep + r->frep);
        new_node->lchild = l;
        new_node->rchild = r;
        push(h, new_node);
    }
    return h->data[1];
}

void extract(HFNode *root, unsigned char *buff, unsigned char (*huffman_code)[SIZE], int n) {
    buff[n] = '\0';
    if (root->lchild == NULL && root->rchild == NULL) {
        strcpy(huffman_code[root->ch], buff);
        return ;
    }
    buff[n] = '0';
    extract(root->lchild, buff, huffman_code, n + 1);
    buff[n] = '1';
    extract(root->rchild, buff, huffman_code, n + 1);
    return ;
}
