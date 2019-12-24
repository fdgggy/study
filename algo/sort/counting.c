/*
当要排序的n个数据，比如最大值是k，k与n相差不多，把数据划分成k个桶，每个桶内的值都是相同。
k与n相差很大则不适合计数排序
只能给非负整数排序
----------------------------------------------------------
        是否原地排序    是否稳定     最好    最坏      平均
计数排序    否             是       O(n)   O(n)       O(n)
----------------------------------------------------------
应用：高考分数排名
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump(int *a, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }   
    printf("\n");
}

//不稳定
void basic_count_sort(int *a, int len) {
    if (len <= 1) {
        return;
    }

    int max = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }

    int size = sizeof(int) * (max+1);
    int *ptr = (int *)malloc(size);
    memset(ptr, 0, size);

    for (int i = 0; i < len; i++) {
        ptr[a[i]]++;
    }
    for (int i = 0; i < max+1; i++) {
        for (int j = 0; j < ptr[i]; j++) {
            printf("%d ", i);
        }
    }

    printf("\n");
}

void count_sort(int a[], int len) {
    if (len <= 1) {
        return;
    }

    int max = a[0];

    for (int i = 1; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    int size = max + 1;

    int *ptr = (int*)malloc(sizeof(int)*size);
    if (ptr == NULL) {
        return;
    }
    memset(ptr, 0, sizeof(int)*size);

    for (int i = 0; i < len; i++) {
        ptr[a[i]]++;
    }

    for (int i = 1; i < size; i++) {
        ptr[i] += ptr[i-1];
    }

    int *ptr2 = (int*)malloc(sizeof(int)*len);
    if (ptr2 == NULL) {
        return;
    }
    memset(ptr2, 0, sizeof(int)*len);

    for (int i = len - 1; i >= 0; i--) {  
        ptr2[ptr[a[i]]-1] = a[i];
        ptr[a[i]]--;   //保证稳定性，还有相同的数据时，下次过来排名顺序变化
    }

    memmove(a, ptr2, sizeof(int)*len);
    free(ptr);
    free(ptr2);
}

int main() {
    int a[5] = { 8, 3, 2, 1, 6 };
    int len = sizeof(a)/sizeof(a[0]);
    printf("len:%d\n", len);

    basic_count_sort(a, len);


    int b[] = { 8, 8, 8 };
    len = sizeof(b)/sizeof(b[0]);
    printf("len:%d\n", len);

    count_sort(b, len);
    dump(b, len);

    return 0;
}