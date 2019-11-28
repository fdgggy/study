/*
存储：
1.所有成员共享一个空间
2.同一时间只有一个成员是有效的
3.union的大小是其最大的成员大小

初始化：
对第一个成员初始化
*/
#include <stdio.h>

typedef union {
    int i;
    char ch[sizeof(int)];
}CHI;

int main() {
    CHI chi;
    chi.i = 0x1234;
    for (int i = 0; i < sizeof(int); i++) {
        printf("%x", chi.ch[i]);//0x34120000  x86架构小端
    }
    printf("\nchi:%ld\n", sizeof(CHI));

    return 0;
}