/*
二分查找/折半查找
递推公式：search(l,r)=search(l,(l+r)/2)
终止条件:
target==a[(l+r)/2]

原理：针对一个有序集合，每次通过跟区间中间元素对比，将待查找区间缩小为之前的一半，直到找到，或者区间缩小为0
时间复杂度：O(logn)
推导过程:
假设数据大小是n，每次查找后数据都会缩小为原来一半。被查找区间的大小变化为
n, n/2, n/4，n/2^k
当n/2^k=1时，k的值就是总共缩小次数，k=log2n，时间复杂度为O(logn)

对数时间复杂度logn是非常高效的时间复杂度，有时比常量级O(1)算法还高效，O(1000)==O(1).
logn即便n非常大，对应的logn也很小，如2^32次方，最多只需要32次。
*/

 #include<stdio.h>

//递归实现
int search(int a[], int target, int left, int right) {
    if (left > right) {  //找不到的情况
        return -1;
    }

    // int middle = (left+right)/2; //如果数比较大，两者之和就会溢出
    int middle = left+((right-left)>>1);
    if (target < a[middle]) {
        return search(a, target, left, middle-1);
    }else if (target > a[middle]){
        return search(a, target, middle+1, right);
    }else {
        return middle;
    }
}

//非递归
int search2(int a[], int size, int target) {
    int left = 0;
    int right = size-1;
    while(left <= right) {
        int middle = left+((right-left)>>1); //偶数个，中间数有2个，就选择较小的，奇数个，则中间数直接算出
        if (a[middle] == target) {
            return middle;
        }else if (target < a[middle]) {
            right = middle - 1;
        }else {
            left = middle + 1; //一定要+/-1，找不到的情况容易造成死循环
        }
    }

    return -1;  //找不到的情况
}

//二分查找变形问题，查找第一个值等于给定值的元素
//递归实现
int search3(int a[], int target, int left, int right) {
    if (left == right) { 
        if (a[left] == target) {
            return left;
        }else {
            return -1;
        }
    }

    int middle = left+((right-left)>>1);
    if (target < a[middle]) {
        return search3(a, target, left, middle-1);
    }else if (target > a[middle]){
        return search3(a, target, middle+1, right);
    }else {
        int res = search3(a, target, left, middle-1);
        return res == -1 ? middle : middle < res ? middle : res;
    }
}

//二分查找变形问题，查找第一个值等于给定值的元素
//非递归
int search4(int a[], int size, int target) {
    int left = 0;
    int right = size-1;
    int min_index = -2;
    while(left <= right) {
        int middle = left+((right-left)>>1); //偶数个，中间数有2个，就选择较小的，奇数个，则中间数直接算出
        if (a[middle] == target) {
            if (min_index != -2) {
                if (middle < min_index) {
                    min_index = middle;
                }
            }else {
                min_index = middle;
            }

            right = middle - 1;
        }else if (target < a[middle]) {
            right = middle - 1;
        }else {
            left = middle + 1; //一定要+/-1，找不到的情况容易造成死循环
        }
    }

    return min_index == -2 ? -1 : min_index;  
}

//二分查找变形问题，查找最后一个值等于给定值的元素
//非递归
int search5(int a[], int size, int target) {
    int left = 0;
    int right = size-1;
    while(left <= right) {
        int middle = left+((right-left)>>1); //偶数个，中间数有2个，就选择较小的，奇数个，则中间数直接算出
        if (a[middle] == target) {
            if (middle==size-1) {
                return middle;
            }
            if (a[middle+1] != target) {
                return middle;
            }
            left = middle + 1;
        }else if (target < a[middle]) {
            right = middle - 1;
        }else {
            left = middle + 1; //一定要+/-1，找不到的情况容易造成死循环
        }
    }

    return -1;  
}

int main() {
     int a[] = {1, 2, 6, 8, 9};
     int len = sizeof(a)/sizeof(a[0]);
     int index = search2(a, len, 8);
     printf("index:%d\n", index);

     int index0 = search(a, 8, 0, len-1);
     printf("index0:%d\n", index0);

     float v = 5.f/2;
     printf("v:%f\n", v); 

     int b[] = {1, 3, 3, 5, 5, 8, 8};
     int len2 = sizeof(b)/sizeof(b[0]);
     int index2 = search3(b, 8, 0, len2-1);
     printf("index2:%d\n", index2);

     int index3 = search4(b, len2, 8);
     printf("index3:%d\n", index3);

     int index5 = search5(b, len2, 5);
     printf("index5:%d\n", index5);

     return 0;
 }