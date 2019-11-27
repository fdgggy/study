#include <stdio.h>

typedef struct {
    char a[10];
    int b;
    char c;
}size_test;

int main() {
    size_test test;
    printf("a:%d\n", sizeof(test));

    return 0;
}