/*************************************************************************
	> File Name: 1.vector.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月28日 星期六 22时40分30秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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


typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector* __init(int);
void clear(Vector *);
int insert(Vector *, int, int);
int delete_element(Vector *, int);
int expand(Vector *);
void output(Vector *);

int main() {
    srand(time(0));
    Vector *v = NULL;
    v = init();
    for (int i = 0; i < 10; i++) {
        int x = rand() % 100, ind = rand() % (i + 3) - 1;
        printf("%d insert(%d, %d) : ", i, x, ind);
        int ret = insert(v, x, ind);
        printf("%d : " , ret);
        output(v);
    }

    for (int i = 0; i < 5; i++) {
        int ind = rand() % (v->length + 2) - 1;
        printf("%d : delete_element(%d) = ", i + 1, ind);
        int ret = delete_element(v, ind);
        printf("%d : ", ret);
        output(v);
    }
    return 0;
}

Vector *__init(int n) {
    Vector *v = (Vector *)malloc2(sizeof(Vector));
    v->data = (int *)malloc2(sizeof(int) * n);
    v->size = n;
    v->length = 0;
    return v;
}

void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

int insert(Vector *v, int val, int ind) {
    if (v->length == v->size && !expand(v)) {
        return 0;
    }
    if (ind < 0 || ind > v->length) {
        return 0;
    }
    for (int i = v->length - 1; i > 0; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = val;
    v->length += 1;
    return 1;
}

int delete_element(Vector *v, int ind) {
    if (ind >= v->length || ind < 0) {
        return 0;
    }
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

int expand(Vector *v) {
    int new_size = v->size;
    int *data;
    while (new_size) {
        data = (int *)realloc(v->data, sizeof(int) * (v->size + new_size));
        if (data == NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    printf("Vector expand ok\n");
    return 1;
}

void output(Vector *v) {
    printf("[");
    for (int i = 0; i < v->length - 1; i++) {
        printf("%d ", v->data[i]);
    }
    printf("%d]\n", v->data[v->length - 1]);
    return ;
}
