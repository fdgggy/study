/*
    函数指针使用场景：
    1.回调函数
 */

#include <stdio.h>

void f1(int a) {
    printf("%d\n", a);
}

int add(int a, int b) {
    return a+b;
}

int sub(int a, int b) {
    return a-b;
}

//函数指针“泛型”用法
int calc(int a, int b, int (*f)(int a, int b)) {
    return f(a, b);
}

int main() {
    //最原始概念，但不会这样用
    int a = 3;
    void (*f)() = &f1;
    (*f)(a);

    int res = calc(1, 2, &add);
    printf("res:%d\n", res);

    res = calc(1, 2, sub);
    printf("res:%d\n", res);
    
    return 0;
}