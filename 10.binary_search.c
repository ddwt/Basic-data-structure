/*************************************************************************
	> File Name: 10.binary_search.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月07日 星期二 22时40分05秒
 ************************************************************************/

#include<stdio.h>


int binary_search(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] < x) {
            head = mid + 1;
        } else {
            tail = mid - 1;
        }
    }
    return -1;
}

//11111110000000
int binary_search2(int *num, int n, int x) {
    int head = -1, tail = n - 1, mid = 0;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) 
            head = mid;
        else
            tail = mid - 1;
    }
    return head;
}


//0000001111111
int binary_search3(int *num, int n, int x) {
    int head = 0, tail = n, mid = 0;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1)
            tail = mid;
        else 
            head = mid + 1;
    }
    return head == n ? -1 : head;
}

void output(int *num, int n) {
    printf("[");
    for (int i = 0; i < n - 1; i++) {
        printf("%d,", num[i]);
    }
    printf("%d]\n", num[n - 1]);
    return ;
}

int main() {
    int num[5] = {1, 2, 4, 3, 5};
    printf("search 1 in num : %d\n", binary_search(num, 5, 1));
    int num1[5] = {1, 1, 1, 0, 0};
    printf("last 1 in num is %d\n", binary_search2(num1, 5, 1));
    int num2[5] = {0, 0, 0, 1, 1};
    printf("first 1 in num is %d\n", binary_search3(num2, 5, 1));
    
    return 0;
}
