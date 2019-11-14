#include <stdio.h>

void print_array(int a[], size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return;
}

int sort(int a[], int low, int high) {
    int pivot = a[low];
    while(low != high) {
        while (low != high && a[high] >= pivot) {
            high--;
        }
        if (low < high) {
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