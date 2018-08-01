/*************************************************************************
	> File Name: 7.heap.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月01日 星期三 14时37分39秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define malloc2(size) (my_malloc(size, __FILE__, __func__, __LINE__))
#define DEFAULTARG(n, x) (#n[0] ? n + 0 : x)
#define init(n) (__init(DEFAULTARG(n, 10)))


void *my_malloc(int size, const char *file, const char *func, const char *line) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "%s : %s -> %s malloc error\n", file, func, line);
        exit(0);
    }
    return data;
}

typedef struct Heap {
    int *data;
    int n, size;
} Heap;

Heap *__init(int);
void clear(Heap *);
int push(Heap *, int);
int expand(Heap *);
void pop(Heap *);
void output(Heap *);

int main() {
    srand(time(0));
    Heap *p = init(21);
    for (int i = 0; i < 20; i++) {
        int value = rand() % 100;
        printf("insert %d to Heap\n", value);
        push(p, value);
        output(p);
    }
    for (int i = 0; i < 20; i++) {
        pop(p);
    }
    output(p);
    
    return 0;
}

Heap *__init(int n) {
    Heap *p = (Heap *)malloc2(sizeof(Heap));
    p->data = (int *)malloc2(sizeof(int) * n);
    memset(p->data, 0, sizeof(int) * n);
    p->size = n;
    p->n = 0;
    return p;
}

void clear(Heap *h) {
    if (h == NULL) return ;
    free(h->data);
    free(h);
    return ;
}

int push(Heap *h, int value) {
    if (h->n == h->size && !expand(h)) return 0;
    h->n += 1;
    h->data[h->n] = value;
    int i = h->n;
    while (i > 1) {
        if (h->data[i] <= h->data[i >> 1]) break;
        h->data[i] ^= h->data[i >> 1];
        h->data[i >> 1] ^= h->data[i];
        h->data[i] ^= h->data[i >> 1];
        i >>= 1;
    }
    return 1;
}

int expand(Heap *h) {
    int new_size = h->size;
    int *data;
    while (new_size) {
        data = (int *)realloc(h->data, sizeof(int) * (h->size + new_size));
        if (data == NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    if (new_size == 0) return 0;
    h->data = data;
    h->size += new_size;
    printf("vector expand\n");
    return 1;
}

void pop(Heap *h) {
    if (h->n <= 1) {
        h->n = 0;
        return ;
    }    
    h->data[1] ^= h->data[h->n];
    h->data[h->n] ^= h->data[1];
    h->data[1] ^= h->data[h->n];
    h->n -= 1;
    int ind = 1;
    while (ind < h->n) {
        int swap_ind = ind;
        if (h->data[ind << 1] > h->data[swap_ind]) {
            swap_ind = ind << 1;
        }
        if (ind << 1 | 1 <=  h->n && h->data[ind << 1 | 1] > h->data[swap_ind]) {
            swap_ind = ind << 1 + 1;
        }
        if (swap_ind == ind) break;
        h->data[ind] ^= h->data[swap_ind];
        h->data[swap_ind] ^= h->data[ind];
        h->data[ind] ^= h->data[swap_ind];
        ind = swap_ind;
    }
    return ;
}

void output(Heap *h) {
    printf("[");
    for (int i = 1; i <= h->size; i++) {
        printf("%d, ", h->data[i]);
    }
    printf("]\n");
    return ;
}
