/*
quick_sort(l...h)=quick_sort(l...p-1)+quick_sort(p+1,h)
l>=h
 */

 #include "../../common/util.h"
//分区
int partition(int a[], int low, int high) {
    int pivot = a[low]; //选最low点为基准
    while(low < high){
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

int partition2(int a[], int low, int high) {
    
}

void quick_sort(int a[], int low, int high) {
    if (low >= high) {
        return;
    }
    int p = partition(a, low, high);
    quick_sort(a, low, p-1);
    quick_sort(a, p+1, high);
}

 int main() {
    int a[] = {5, -3, 2, 9, 1};
    // int a[] = {5, 6, 7, 9, 10};

    int len = sizeof(a)/sizeof(a[0]);
    print_array(a, len);

    quick_sort(a, 0, len-1);
    printf("----------------------\n");
    print_array(a, len);

    return 0;
 }