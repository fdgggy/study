/*
归并排序
递推公式
merge_sort(p...r)=merge(merge_sort(p...q), merge_sort(q+1...r))  q=(p+r)/2
终止条件：p>=r

原理：把数组从中间分成前后两部分，对前后两部分分别排序，再将排好序的部分合并在一起

时间复杂度：nlogn
推导过程：
递归：一个问题a分解为多个子问题b,c， b,c解决后，再把b,c的结果合并成a的结果。
定义解决问题a的时间是T(a), b,c分别是T(b)和T(c),则递推公式：
T(a)=T(b)+T(c)+k    k为将两个子问题b,c结果合并成问题a的结果所消耗的时间。

对n个元素进行归并排序需要的时间是T(n)，2个子数组排序的时间都是T(n/2)。Merge函数合并两个有序数组的时间复杂度是O(n)。则：
T(1)=C; n=1时，只需要常量级的执行时间，所有表示为C。
T(n)=2*T(n/2)+n; n>1
因为:T(n/2)=2T(n/4)+n/2
所以:T(n)=2*(2T(n/4)+n/2)+n=4*T(n/4)+2*n  第二次递归
因为:T(n/4)=2*T(n/8)+n/4
所以:T(n)=4*(2*T(n/8)+n/4)+2*n=8*T(n/8)+3*n  第三次递归
推断出
T(n)=2^k*T(n/2^k)+kn
当n,k无穷大时，总有n/2^k=1, 则T(n/2^k)=T(1) -->k=log2n
则T(n)=2^(log2n)T(1)+nlog2n   
2^(log2n)=n
所以
T(n)=nT(1)+nlog2n=Cn+nlog2n
用大O表示，T(n)=O(nlogn)

空间复杂度：
归并排序在任何情况下时间复杂度都是O(nlogn)，致命弱点，不是原地排序，需要额外分配内存空间。
不能类似时间复杂度推导，每次合并操作都需要额外申请内存，但合并完成后，临时开辟的内存都被释放了，在任意时刻，cpu只会再一个函数执行，
也就只会有一个临时的内存空间在使用，临时空间最大不会超过n个数据的大小，所以空间复杂度是O(n)。
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
    free(temp);
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