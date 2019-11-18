/*
快速排序
递推公式:
quick_sort(q...r)=quick_sort(p...q-1)+quick_sort(q+1, r)
终止条件：p >= r

原理：选择p-r任意一个数据作为pivot(分区点),遍历p-r间的数据，小于pivot的放在左边，大于pivot的放到右边，将pivot放到中间。
      递归排序下标从p到q-1之间的数据和小标从q+1到r之间的数据，直到区间小于1,说明所有数据都有序。
 */
#include <stdio.h>

void print_array(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}

int sort(int a[], int low, int high) {
    int pivot = a[low];//选最low点为基准
    while(low != high) {
        while (low != high && a[high] >= pivot) {//本来就是有序的, low=high
            high--;
        }
        if (low < high) {//本来就是有序的, low=high
            a[low] = a[high];
        }

        while(low != high && a[low] <= pivot) {
            low++;
        }
        if (low < high) {
            a[high] = a[low];
        }
    }
    a[low] = pivot;
    return low;
}

int sort2(int a[], int low, int high) {
    int i, j;
    i = j = low;

    for (; j < high; j++) {
        if (a[j] < a[high]) {
            if (i != j) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            i++;
        }
    }
    if (i != high) {
        int temp = a[i];
        a[i] = a[high];
        a[high] = temp;
    }
    return i;
}

void quick_sort(int a[], int low, int high) {   
    if (low < high) {
        int index = sort2(a, low, high);
        printf("index:%d\n", index);
        quick_sort(a, low, index-1);
        quick_sort(a, index+1, high);
    }
}

int main() {
    printf("quick sort\n");

    int a[] = {5, 1, -3, 9, 2, 8};
    int len = sizeof(a)/sizeof(a[0]);
    print_array(a, len);
    quick_sort(a, 0, len-1);
    printf("--------\n");
    print_array(a, len);

    return 0;
}