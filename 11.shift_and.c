/*************************************************************************
	> File Name: shift_and.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月05日 星期日 16时29分13秒
 ************************************************************************/

#include<stdio.h>

#define TEST(func) { \
    printf("%s : = %d\n", #func, func); \
}

int shift_and2(const char *text, const char *pattern) {
    int d[127][127] = {0}, n = 0;
    for (; pattern[n]; n++) {
        d[pattern[n]][n] = 1;
    }
    int p[127] = {0}, k = 0;
    for (int i = 0; text[i]; i++) {
        //printf("i = %d\n", i);
        for (int i = 0; i < 127; i++) {
            p[i + 1] = p[i];
        }
        p[0] = 1;
        for (int j = 0; j < 127; j++) {
	        p[j] = d[text[i]][j] & p[j];
            if (p[n - 1] == 1) return 1;
        }
        
    }
    return 0;
}

int main() {
    TEST(shift_and2("hello world", "world"));
    TEST(shift_and2("hello world", "x"));
    return 0;
}
