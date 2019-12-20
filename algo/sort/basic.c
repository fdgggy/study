/*
虽然冒泡排序和插入排序的时间复杂度上是一样的，都是O(n^2)，但是会首选插入排序，因为冒泡排序交换需要3个赋值操作，插入排序只需要1个，
如果数量级很大时，虽然时间复杂度相同，但是插入排序性能更优。TODO 实验

小结：
评价排序算法从：
1.执行效率
2.内存消耗
3.稳定性
----------------------------------------------------------
        是否原地排序    是否稳定     最好    最坏      平均
冒泡排序    是             是       O(n)   O(n^2)    O(n^2)
插入排序    是             是       O(n)   O(n^2)    O(n^2)  ****实际中运用最多  TODO 希尔排序
选择排序    是             否       O(n^2) O(n^2)    O(n^2)
----------------------------------------------------------
 */
#include <stdio.h>
//创建临时变量
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//不创建临时变量
void swap2(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

/*
位运算, 异或运算符。
二进制位同号为0,异号为1。0^0=0 0^1=1 1^0=1 1^1=0
1.特定位翻转
2.两个值的交换，不需要申请临时变量
 */
void swap3(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
/*
冒泡:
1.每次冒泡操作都会对相邻2个元素比较，互换
2.一次冒泡让至少一个元素移动到它应该在的位置
3.重复n次，就完成了n个数据的排序

分析:
1.原地排序(空间复杂度O(1))。只涉及相邻数据的交换。
2.稳定排序(序列中相等的元素排序后并不改变原有先后顺序)。
3.最好情况时间复杂度是O(n)，最坏情况时间复杂度O(n^2)。TODO 平均时间复杂度O(n^2)
 */
void bubble(int a[], int len) {
    if (len <= 1) {
        return;
    }

    for (int i = 0; i < len; i++) {
        int ok = 0;
        for (int j = 0; j < len-i-1; j++) {
            if (a[j] > a[j+1]) {
                ok = 1;
                swap3(&a[j], &a[j+1]);
            }
        }
        if (ok == 0) {
            break;
        }
    }
}
/*
插入：
1.数组分为已排序区间和未排序区间
2.取未排序区间中的元素在已排序区间中找到合适的插入位置插入，并保证已排序区间数据一致有序
3.重复这个过程，知道未排序区间中元素为空

分析：
1.原地排序
2.稳定排序
3.最好时间复杂度是O(n)，最坏情况时间复杂度O(n^2)。平均时间复杂度O(n^2)
 */
void insert(int a[], int len) {
    if (len <= 1) {
        return;
    }

    for (int i = 1; i < len; i++) {
        int value = a[i];
        int j = i-1;
        for (;j >= 0; j--) {
            if (a[j] > value) {
                a[j+1] = a[j];
            }else {
                break;
            }
        }
        a[j+1] = value;
    }
}
/*
选择：
1.数组分为已排序区间和未排序区间
2.每次从未排序区间中找到最小元素放入已排序区间末尾

分析：
1.原地排序
2.不稳定。(5,8,5,2  第一个5先和2换位置，换了后就在第二个5的后面，顺序打乱了)
3.最好时间复杂度是O(n^2)，最坏情况时间复杂度O(n^2)。平均时间复杂度O(n^2)
 */
void select(int a[], int len) {
    if (len <= 1) {
        return;
    }

    int min;
    for (int i = 0; i < len-1; i++) {
        min = i;

        for (int j = i+1; j < len; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        if (i != min) {
            swap3(&a[min], &a[i]);
        }
    }
}

void dump(int a[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[] = { 5, 3, 2, 1, 6, 9 };
    int len = sizeof(a)/sizeof(a[0]);
    dump(a, len);
    bubble(a, len);
    printf("after bubble\n");
    dump(a, len);

    int b[] = { 5, 3, 2, 1, 6, 9 };
    int b_len = sizeof(b)/sizeof(b[0]);
    insert(b, b_len);
    printf("after insert\n");
    dump(b, b_len);

    int c[] = { 5, 3, 2, 1, 6, 9 };
    int c_len = sizeof(c)/sizeof(c[0]);
    insert(c, c_len);
    printf("after select\n");
    dump(c, c_len);

    return 0;
}