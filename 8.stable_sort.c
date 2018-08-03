/*************************************************************************
	> File Name: 8.stable_sort.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月03日 星期五 14时23分52秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a, b) { \
    __typeof(a) temp; \
    temp = b; b = a; \
    a = temp; \
}

#define TEST(n, func) { \
    int num[30] = {0}; \
    printf("["); \
    for (int i = 0; i < 30; i++) { \
        num[i] = rand() % 100; \
        printf("%d ", num[i]); \
    } \
    printf("]\n"); \
    func; \
    output(num, n, #func); \
}

void insert_sort(int *, int);
void bubble_sort(int *, int);
void merge_sort(int *, int, int);
void output(int *, int, const char *);

int main() {
    srand(time(0));
    TEST(30, insert_sort(num, 30));
    TEST(30, bubble_sort(num, 30));
    TEST(30, merge_sort(num, 0, 29));
    return 0;
}

void insert_sort(int *num, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (num[j + 1] >= num[j]) break;
            swap(num[j + 1], num[j]);
        }
    }
    return ;
}

void bubble_sort(int *num, int n) {
    int flag = 1;
    for (int i = 0; i < n && flag; i++) {
        flag = 0;
        for (int j = 0; j < n - 1; j++) {
            if (num[j] > num[j + 1]) {
                flag = 1;
                swap(num[j], num[j + 1]);
            }
        }
    }
    return ;
}

void merge_sort(int *num, int l, int r) {
    if (r == l) return ;
    int mid = (l + r) >> 1;
    merge_sort(num, l, mid);
    merge_sort(num, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int x = l, y = mid + 1, k = 0;
    while (x <= mid || y <= r) {
        if (y > r || (x <= mid && num[x] <= num[y])) {
            temp[k++] = num[x++];
        } else {
            temp[k++] = num[y++];
        }
    }
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return ;
}

void output(int *num, int n, const char *func) {
    for (int i = 0; i < n; i++) {
        if (i == 0) 
            printf("%d", num[i]);
        else
            printf(" %d", num[i]);
    }
    printf("\n");
    return ;
}
