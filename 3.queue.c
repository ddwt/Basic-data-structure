/*************************************************************************
	> File Name: 3.queue.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 09时54分34秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define malloc2(size) my_malloc(size, __FILE__, __func__, __LINE__)

#define DEFAULTARG(n, x) (#n[0] ? n + 0 : x)
#define init(n) (__init(DEFAULTARG(n, 10)))

#define data_type int
#define NULL_VALUE -15555

void *my_malloc(int size, const char *file, const char *func, int line_no) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "[%s : %s-> %d] malloc error\n", file, func, line_no);
        fflush(stderr);
        exit(-1);
    }
    return data;
}

typedef struct Queue {
    data_type *data;
    int head, tail;
    int length;
    int count;
} Queue;

Queue *__init(int);
void clear(Queue *);
int push(Queue *, data_type);
int pop(Queue *);
int expand(Queue *);
data_type front(Queue *);
int empty(Queue *);
void output(Queue *);




int main() {
    srand(time(0));
    Queue *q = init(10);
    for (int i = 0; i < 20; i++) {
        int op = rand() % 2, value = rand() % 100;
        if (op == 1)  {
            printf("insert %d to queue\n", value);
            push(q, value);
            output(q);
        } else {
            printf("pop element from queue = %d\n", pop(q));
            output(q);
        }
    }
    return 0;
}

Queue *__init(int n) {
    Queue *q = (Queue *)malloc2(sizeof(Queue));
    q->data = (data_type *)malloc2(sizeof(data_type) * n);
    q->head = 0;
    q->tail = -1;
    q->count = 0;
    q->length = n;
    return q;
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int push(Queue *q, data_type value) {
    if (q->count == q->length && !expand(q)) return 0;
    q->tail = (q->tail + 1) % q->length;
    q->count += 1;
    q->data[q->tail] = value;
    return 1;
}

int pop(Queue *q) {
    if (empty(q)) return 0;
    q->count -= 1;
    q->head = (q->head + 1) % q->length;
    return 1;
}

int expand(Queue *q) {
    int new_length = q->length;
    data_type *data;
    while (new_length) {
        data = (data_type *)realloc(q->data, sizeof(data_type) * (q->length + new_length));
        if (data == NULL) {
            new_length >>= 1;
            continue;
        }
        break;
    }
    if (new_length == 0) return 0;
    q->data = data;
    q->length += new_length;
    printf("Queue expand ok\n");
    return 1;
}
data_type front(Queue *q) {
    if (empty(q)) return NULL_VALUE;
    return q->data[q->head];
}

int empty(Queue *q) {
    return q->count == 0;
}

void output(Queue *q) {
    printf("[");
    for (int i = 0, head = q->head;
        i < q->count;
        i++, head = (head + 1) % q->length) {
        printf("%d, ", q->data[head]);
    }
    printf("]\n");
    return ;
}
