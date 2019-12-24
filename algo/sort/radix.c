/*
基数排序： 按照个位来排序，再按照十位，一直到最大数的最高位排序。按某位排序时用计数排序即可.
应用场景：排序10万个手机号码
时间复杂度：计数排序时O(n), 要排序的数据有k位，则O(k*n),k不大时为常数，则基数排序时间复杂度近似于O(n)。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../common/util.h"

//gcc radix.c -lm   pow

#define NUM_OF_POS(a, v) ((a)/v)%10

void raidx_sort(int *a, int len) {
    if (len <= 1) {
        return;
    }

    int temp[10] = {0};
    int temp2[len];

    int max = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    int num = 1;
    while (max/10 > 0) {
        num++;
        max /= 10;
    }

    for (int i = 0; i < num; i++) {
        memset(temp, 0, sizeof(int)*10);
        memset(temp2, 0, sizeof(int)*len);

        int pval = pow(10, i);  //求出当前基数

        for (int j = 0; j < len; j++) {
            int index = NUM_OF_POS(a[j], pval);
            temp[index]++;
        }

        for (int j = 1; j < 10; j++) {
            temp[j] += temp[j-1];
        }

        for (int j = len-1; j >= 0; j--) {
            int index = NUM_OF_POS(a[j], pval);
            temp2[temp[index]-1] = a[j];

            temp[index]--;
        }

        memmove(a, temp2,  sizeof(int)*len);
    }
}

int main() {
    int a[] = {123, 122999, 1234, 2567};
    int len = sizeof(a)/sizeof(a[0]);
    print_array(a, len);

    raidx_sort(a, len);
    print_array(a, len);

    return 0;
}