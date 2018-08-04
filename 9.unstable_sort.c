/*************************************************************************
	> File Name: 9.unstable_sort.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月04日 星期六 23时14分17秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <string.h>

#define swap(a, b) { \
    __typeof(a) temp; \
    temp = a; \
    a = b; \
    b = temp; \
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

void select_sort(int *, int);
void quick_sort(int *, int, int);
void output(int *, int, const char *);

int main() {
    srand(time(0));
    TEST(30, select_sort(num, 30));
    TEST(30, quick_sort(num, 0, 29));
    
    return 0;
}

void select_sort(int *num, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (num[j] < num[ind]) ind = j;
        }
        swap(num[ind], num[i]);
    }
}

void quick_sort(int *num, int l, int r) {
    while (r - l >= 2) {
        int x = l, y = r, z = num[rand() % (r - l + 1) + l];
        do {
            while (num[x] < z) ++x;
            while (num[y] > z) --y;
            if (x <= y) {
                swap(num[x], num[y]);
                ++x, --y;
            }
        }while(x <= y);
        quick_sort(num, l, y);
        l = x;
    }
    ungarded_insert_sort(num + l, r - l + 1);
    return ;
}

void ungarded_insert_sort(int *num, int n) {
    int ind = 0;
    for (int i = 1; i < n; i++) {
        if (num[i] < num[ind]) ind = i;
    }
    swap(num[ind], num[0]);
    for (int i = 2; i < n; i++) {
        int j = i;
        while (num[j] < num[j - 1]) {
            swap(num[j], num[j - 1]);
            j--;
        }
    }
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
}
