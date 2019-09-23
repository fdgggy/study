#include <stdio.h>

int main(int argc, char* argv[]){
    int i = 0;
    int arr[3] = {0};
    printf("&i:%x\n", &i);
    for(; i<=3; i++){  //gcc 添加编译选项-fno-stack-protector，关闭堆栈保护，则会出现死循环
        arr[i] = 0;
        printf("hello world &arr[i]:%x i:%d\n", &arr[i], i);
    }   

    return 0;
}