*********************************************************
	> File Name: 2.linklist.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月28日 星期六 23时20分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define malloc2(size) my_malloc(size, __FILE__, __func__, __LINE__)

#define DEFAULTARG(n, x) (#n[0] ? n + 0 : x)
#define init(n) (__init(DEFAULTARG(n, 10)))

void *my_malloc(int size, const char *file, const char *func, int lin_num) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "%s : %s->%d malloc error\n", file, func, lin_num);
        fflush(stderr);
        abort();
    }
}

typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList {
    LinkNode *head;
    int n;
} LinkList;

LinkList *__init();
void clear(LinkList *);
LinkNode *getNewNode(int);
int insert(LinkList *, int, int);
int deleteNode(LinkList *l, int ind);
void output(LinkList *);


int main() {
    srand(time(0));
    LinkList *l = init();
    for (int i = 0; i < 10; i++) {
        int data = rand() % 100, ind = rand() % (i + 3) - 2;
        printf("%d : insert(%d, %d) = ", i, data, ind);
        fflush(stdout);
        printf("%d :", insert(l, data, ind));
        output(l);
    }
    
    return 0;
}

LinkList *__init(int n) {
    LinkList *l = (LinkList *)malloc2(sizeof(LinkList));
    l->head = NULL;
    l->n = 0;
    return l;
}

void clear(LinkList *l) {
    LinkNode *head = l->head;
    while (head) {
        LinkNode *next = head->next;
        free(head);
        head = next;
    }
    free(l);
    return ;
}

LinkNode *getNewNode(int data) {
    LinkNode *p = (LinkNode *)malloc2(sizeof(LinkNode));
    p->data = data;
    p->next = NULL;
    return p;
}

int insert(LinkList *l, int data, int ind) {
    if (ind < 0 || ind > l->n) return 0;
    LinkNode ret, *p;
    ret.next = l->head;
    p = &ret;
    while (p && ind--) {
        p = p->next;
    }
    LinkNode *new_node = getNewNode(data);
    new_node->next = p->next;
    p->next = new_node;
    l->head = ret.next;
    l->n += 1;
    return 1;
}

int deleteNode(LinkList *l, int ind) {
    if (ind < 0 || ind >= l->n) return 0;
    LinkNode ret, *p;
    ret.next = l->head;
    p = &ret;
    while (p && ind--) {
        p = p->next;
    }
    LinkNode *del = p->next;
    p->next = del->next;
    free(del);
    return 1;
}

void output(LinkList *l) {
    LinkNode *head = l->head;
    while (head) {
        printf("%d ->", head->data);
        head = head->next;
    }
    printf("null\n");
}
