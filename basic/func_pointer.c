/*
    常量指针：
    1.字符串常量指针，如"abc"，直接作为指针基址
    2.指针指向的内容不可变，但指针本省可以变。const int *a;
    3.指针本身不可变，指向内容可变。int *const a；
    4.指针本身不可变，指向内容也不可变  const int *const a;
------------------------------------------------------------------------
    函数指针概述：
    函数指针可以达到泛型的作用，标准库中的qsort就是采用回调函数的方法

    函数指针使用场景：
    1.回调函数

    数组指针int(*p)[3],
    char* const*(*next)*(),next是一个指向函数的指针，该函数返回另一个指针
    该指针指向一个只读的指向char的指针

    如何解释或定义复杂的声明
    1.从左边找到第一个标识符
    2.找标识符左边的[或(，[就是声明一个数组，剩下的部分都是在描述数组里保存的类型
      如果找到(，就是声明一个函数，表达式剩余都是在描述这个函数的返回值。
    3.如果没有[或(，找到*，就是一个指针，剩余部分都是在描述指针指向的类型。
    4.从上到下逐层分析
    5.从下到上利用typedef逐层定义

    小结：再复杂的声明无非就是数组，函数，指针3种
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

//void (*ap[10](void(*)()))
typedef void (*pfv)();
typedef void (*pf_pfv)(pfv);

typedef int (*calclate)(int a, int b);

int add_ex(int a, int b) {
    return a+b;
}

int sub_ex(int a, int b) {
    return a-b;
}

int calc_num(int a, int b, calclate func) {
    return func(a, b);
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
    
    pf_pfv ap[10];
    
    res = calc_num(1, 2, add_ex);
    printf("calc_num add res:%d\n", res);

    res = calc_num(1, 2, sub_ex);
    printf("calc_num sub res:%d\n", res);

    return 0;
}