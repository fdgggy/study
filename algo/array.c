//大小固定的有序数组，支持动态增删改操作
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array {
    int size;
    int used;
    int *arr;
};

void dump(struct array *array) {
    if (!array) {
        printf("array is null\n");
        return;
    }

    if (!array->arr) {
        printf("array->arr is null\n");
        return;
    }

    for (int i = 0; i < array->used; i++) {
        printf("index:%d value:%d\n", i, array->arr[i]);
    }
}

void alloc(struct array *array) {
    array->arr = (int*)malloc(sizeof(int)*10);
    if (!array->arr) {
        printf("malloc failed, array->arr is null\n");
        return;
    }

    memset(array->arr, 0, sizeof(int)*40);
}

//有序插入
int insert(struct array *array, int value) {
    if (!array || !array->arr) {
        return -1;
    }

    if (array->used >= array->size) {
        return -1;
    }

    int index = 0;
    for (index= 0; index < array->used; index++) {  
        if (value < array->arr[index]) {
            //复制字节字符串
            memmove(&array->arr[index+1], &array->arr[index], (array->used-index)*sizeof(int)); 
            break;
        }
    }   

    //索引为0的也满足
    array->arr[index] = value;
    array->used++;

    return index;
}

int delete(struct array *array, int index) {
    if (!array || !array->arr) {
        return -1;
    }

    if (index < 0 || index >= array->used) {
        return -1;
    }

    memmove(&array->arr[index], &array->arr[index+1], (array->used-index-1)*sizeof(int)); 
    array->used--;
}

int search(struct array *array, int value) {
    if (!array || !array->arr) {
        return -1;
    }

    for (int index= 0; index < array->used; index++) {  
        if (array->arr[index] == value) {
            return index;
        }

        //优化点，但凡比数组任意元素小，则返回。数组为有序数组。
        if (array->arr[index] > value) {
            return -1;
        }
    }

    return -1;
}

int main() {
    struct array ar = {10, 0, NULL};
    alloc(&ar);

    insert(&ar, 3);
    printf("insert 3\n");
    dump(&ar);

    insert(&ar, 2);
    printf("insert 2\n");
    dump(&ar);

    insert(&ar, 1);
    printf("insert 1\n");
    dump(&ar);

    delete(&ar, 0);
    printf("delete index 0\n");
    dump(&ar);

    int result = search(&ar, 3);
    printf("search result:%d\n", result);

    return 0;
}
