#include <stdio.h>
//a[i]_addr = base_addr + i*datasize
int main(int argc, char* argv[]){
    int a[2] = {1, 2};
    printf("a:%p\n", a);       //数组a就代表a[0]的地址
    printf("a[0]:%p\n", &a[0]);
    printf("a[1]:%p v:%d\n", a+1, *(a+1));  //+1代表加上一个sizeof(data)的偏移

    int i = 1;
    if (i++ == 1) { //i++先运算表达式，再自增, ++i相反
        printf("aaa\n");
    }
    printf("i:%d\n", i);
    return 0;
}