/*************************************************************************
	> File Name: 4.stack.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 10时40分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define data_type int
#define NULL_VALUE -16666

#define malloc2(size) my_mylloc(size, __FILE__, __func__, __LINE__)

#define DEFAULTARG(n, x) (#n[0] ? n + 0 : x)
#define init(n) (__init(DEFAULTARG(n, 10)))

void *my_mylloc(int size, const char *file, const char *func, int line_no) {
    void *data = malloc(size);
    if (data == NULL) {
        fprintf(stderr, "[%s : %s-> %d] malloc error\n", file, func, line_no);
        fflush(stderr);
        exit(-1);
    }
    return data;
}

typedef struct Stack {
    data_type *data;
    int top, size;
} Stack;

Stack *__init(int);
void clear(Stack *);
int push(Stack *, data_type);
int pop(Stack *);
int expand(Stack *);
data_type top(Stack *);
int empty(Stack *);
void output(Stack *);



int main() {
    srand(time(0));
    Stack *s = init(20);
    for (int i = 0; i < 20; i++) {
        int op = rand() % 2, value = rand() % 100;
        switch (op) {
            case 0:
                printf("push element = %d to stack\n", value);
                push(s, value);
                output(s);
                break;
            case 1:
                printf("pop element from stack\n");
                pop(s);
                output(s);
                break;
            default:
                fprintf(stderr, "error operator = %d\n", op);
                break;
        }
    }
    
    return 0;
}
Stack *__init(int n) {
    Stack *s = (Stack *)malloc2(sizeof(Stack));
    s->data = (data_type *)malloc2(sizeof(data_type) * n);
    s->top = -1;
    s->size = n;
    return s;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int push(Stack *s, data_type value) {
    if (s->top + 1 == s->size && !expand(s)) return 0;
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}

int pop(Stack *s) {
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

int expand(Stack *s) {
    int new_size = s->size;
    data_type *data;
    while (new_size) {
        data = (int *)realloc(s->data, sizeof(int) * (s->size + new_size));
        if (data = NULL) {
            new_size /= 2;
            continue;
        }
        break;
    }
    if (new_size == 0) return 0;
    s->data = data;
    s->size += new_size;
    printf("stack expand ok\n");
    return 1;
}

data_type top(Stack *s) {
    if (empty(s)) return NULL_VALUE;
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

void output(Stack *s) {
    int ret = 0, last_pos = 0;
    ret += printf("[");
    for (int i = 0; i < s->size; i++) {
        if (i <= s->top) {
            ret += printf("%d", s->data[i]);
            last_pos = ret - 1;
        }
        ret += printf(",");
    }
    ret += printf("]\n");
    for (int i = 0; i < last_pos; i++) {
        printf(" ");
    }
    printf("\n");
    for (int i = 0; i < last_pos; i++) {
        printf(" ");
    }
    printf("|\n");
    for (int i = 0; i < last_pos - 1; i++) {
        printf(" ");
    }
    printf("top/\n\n");
    return ;
}
