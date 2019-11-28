/*
声明和定义变量的区别：
1.定义创建了变量，并为其分配内存，声明没有分配内存
2.一个变量在一定区域只能被定义一次，可以被声明多次
 */
#include <stdio.h>

extern int ex;  //声明变量已经在其他地方定义过了， 并不为其分配内存
extern void print(int b);

// int ex; //再次定义时，则会被外部定义的变量所覆盖,值为6

int main() {
    print(ex);
    print(12);

    return 0;
}
