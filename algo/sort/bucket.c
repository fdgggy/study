/*
桶排序：将排序数据分到几个有序的桶里，每个桶里的数据再单独进行排序，桶内排序完后，再把每个桶里的数据按照顺序依次取出，组成的序列就是有序的了。
时间复杂度：O(n)

推导：如果排序数据n个，均匀的分配到m个桶，每个桶有k=n/m个元素。每个桶内使用快排，时间复杂度是O(k*logk)，m个桶排序的时间复杂度为O(m*k*logk)
因为k=n/m, 则整个桶时间复杂度是O(n*log(n/m))，当桶的个数m接近n时，log(n/m)就是一个非常小的常量，则桶排序时间复杂度接近O(n)

桶排序不能替代之前的排序算法
1.要排序的数据要很容易划分成m个桶，桶之间有着天然大小顺序
2.数据再各个桶之间的分布要比较均匀。如果有的桶数据非常多，有的非常少，很不平均。极端情况下，都被分到一个桶里，那就退化成O(nlogn)

应用场景：
适合外部排序，即数据存储在外部磁盘中，数据量比较大，内存有限，无法将数据全部加载到内存.
1.扫描所有文件，划分桶
2.将桶内文件依次放入内存，用快排排序
3.所有文件都排好序后，按照文件编号，依次存储在另一个文件
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../common/util.h"

typedef struct {
    int node[10];
    int count;
}bucket;

int partition(int a[], int low, int high) {
    int pivot = a[low];
    while(low < high) {
        while(low < high && a[high] > pivot){ //本来就是有序的, low=high
            high--;
        }

        if (low < high) { //本来就是有序的, low=high
            a[low] = a[high];
        }

        while(low < high && a[low] < pivot) {
            low++;
        }

        if (low < high) {
            a[high] = a[low];
        }
    }

    a[low] = pivot;
    return low;
}

void quick_sort(int a[], int low, int high) {
    if (low >= high) {
        return;
    }

    int p = partition(a, low, high);
    quick_sort(a, low, p-1);
    quick_sort(a, p+1, high);
}

void bucket_sort(int a[], int len) {
    if (len <= 1) {
        return;
    }

    bucket *p_bucket;
    int min, max, num;
    min = max = a[0];
    for (int i = 1; i < len; i++) {
        if (a[i] > max) {
            max = a[i];
        }else if (a[i] < min) {
            min = a[i];
        }
    }

    num = (max-min+1)/10+1;  //0-21
    p_bucket = (bucket*)malloc(sizeof(bucket)*num);
    if (p_bucket == NULL) {
        return;
    }
    memset(p_bucket, 0, sizeof(bucket)*num);

    for (int i = 0; i < len; i++) {
        int index = (a[i]-min+1)/10;
        bucket *b = p_bucket+index;
        b->node[b->count] = a[i];
        b->count++;
    }

    int pos = 0;
    for (int i = 0; i < num; i++) {
        bucket *b = p_bucket+i;
        if (b->count > 0) {
            quick_sort(b->node, 0, (b->count)-1);

            for (int j = 0; j < b->count; j++) {
                a[pos++] = b->node[j];
            }
        }
    }

    free(p_bucket);
}

int main() {
    int a[] = {5, -3, 2, 9, 1};
    // int a[] = {5, 6, 7, 9, 10};

    int len = sizeof(a)/sizeof(a[0]);
    print_array(a, len);
    // quick_sort(a, 0, len-1);
    printf("----------------------\n");

    bucket_sort(a, len);
    print_array(a, len);

    return 0;
}



