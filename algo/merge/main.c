/*
归并排序
递推公式
merge_sort(p...r)=merge(merge_sort(p...q), merge_sort(q+1...r))  q=(p+r)/2
终止条件：p>=r

原理：把数组从中间分成前后两部分，对前后两部分分别排序，再将排好序的部分合并在一起
 */

#include <stdio.h>

void print_array(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}

void merge(int a[], int left, int middle, int right) {
    int *temp = (int*)malloc((right-left+1)*sizeof(int));
    int i = 0;
    int p1 = left;
    int p2 = middle + 1;
    while(p1 <= middle && p2 <= right) {
        temp[i++] = a[p1] < a[p2] ? a[p1++] : a[p2++];
    }

    while(p1 <= middle) {
        temp[i++] = a[p1++];
    }

    while(p2 <= right) {
        temp[i++] = a[p2++];
    }

    memcpy(a+left, temp, (right-left+1)*sizeof(int));
}

void merge_sort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = (left+right)/2;
    merge_sort(a, left, mid);
    merge_sort(a, mid+1, right);
    merge(a, left, mid, right);
}

int main() {
    int a[] = {5, -1, 3, 8, 0, -5, 7};

    int len = sizeof(a)/sizeof(a[0]);
    print_array(a, len);
    merge_sort(a, 0, len-1);
    printf("----------------------------\n");
    print_array(a, len);

    return 0;
}