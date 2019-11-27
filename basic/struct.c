/*
c: 1.整型(字符，短整型，整型，长整型) 2.浮点型 3.指针 4.聚合类型(数组和结构)
*长整型至少应该和整型一样长，而整型至少应该和短整型一样长。* -> c和指针

不同系统下c语言各类型长度,绝大部分64位unix,linux使用LP64模型，32位linux使用ILP32模型
Data Type        ILP32       LP64
char              1            1
short             2            2
int               4            4
long              4            8
long long         8            8

float             4            4
double            8            8

pointer           4            8

对齐系数: 32位平台上编译器默认系数一般是4,64位一般是8
有效对齐系数：对齐系数和结构体中最长数据类型中较小的那个
内存对齐: 数据的首地址是某个数(min(对齐系数,自身长度))的倍数。

基本数据类型对齐规则:
地址只要是它的长度整数倍即可。

数组对齐规则:
按照基本数据类型对齐规则，第一个对齐了，后面的自然也对齐了。

联合对齐规则:
包含的最长数据类型对齐。

结构体对齐规则：
1.第一个成员的偏移量为0，以后每个成员相对于结构体首地址的偏移都是该成员大小与有效对齐系数较小那个的正数倍
2.(补齐)结构体总大小为有效对齐系数的整数倍，不足的话编译器会加上填充字节。

为什么要进行对齐
提高cpu访问数据的效率。大部分cpu(x86架构)都是以字(2字节)/双字/4字...为单位读取内存的，并从偶地址开始,如果子单元从偶地址开始，那么只需要访问一次内存即可，
如果从奇地址开始，则需要2次。
 */

#include <stdio.h>

typedef unsigned char BYTE;
typedef enum {
    RED=0x01, 
    BLUE, 
    GREEN, 
    YELLOW, 
    BLACK
}Color;

// #pragma pack(4)  //24
// #pragma pack(8)  //32
#pragma pack(2)  //18

typedef struct {
    BYTE has_skylight;  //0-1
    Color color;   //2-5
    BYTE auto_shift;//6-7
    double price;//8-15
    BYTE seat_num;//16-17
}Mycar;

int main() {
    Mycar car, *acar;
    int a= 3;
    int *ab = &a;
    printf("car:%ld a:%ld ab:%ld\n", sizeof(car), sizeof(acar), sizeof(ab));

    return 0;
}