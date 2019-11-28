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
    // char ch[sizeof(int)];
    char ch[18];
}CHI;

typedef struct {  //union算大小也是按照对齐补齐策略
    double i;
    CHI j;  //计算大小时按照整个占用空间算
}Test;

int main() {
    CHI chi;
    chi.i = 0x1234;
    for (int i = 0; i < sizeof(int); i++) {
        printf("%x", chi.ch[i]);//0x34120000  x86架构小端
    }
    printf("\nchi:%ld\n", sizeof(CHI));
    printf("test:%ld\n", sizeof(Test));

    return 0;
}