/*
顺序循环队列
先进先出，队尾插入，对头删除
关键是对空对满判断
当队列满时，tail指向的位置是没有存储数据的。所以，顺序循环队列会浪费一个数组元素存储空间。
 */
#include <stdio.h>
#include <stdlib.h>

#define queue_full(q) ((q->tail+1)%(q->capacity) == q->head)
#define queue_empty(q) (q->head == q->tail)

typedef struct {
    int head;
    int tail;
    int capacity;
    int *data;
}queue;

queue *create_queue(int capacity) {
    queue *q = (queue *)malloc(sizeof(queue));
    if (q == NULL) {
        printf("create_queue failed, queue is null\n");
        return NULL;
    }

    int *p = (int *)malloc(sizeof(int)*capacity);
    if (p == NULL) {
        printf("create_queue failed, data is null\n");
        return NULL;
    }

    q->capacity = capacity;
    q->data = p;
    q->head = q->tail = 0;

    return q;
}

int enqueue(queue *q, int data) {
    if (q == NULL) {
        return -1;
    }

    if (queue_full(q)) {
        printf("enqueue failed, queue is full\n");
        return -1;
    }

    q->data[q->tail] = data;
    q->tail = (q->tail+1)%(q->capacity);
}

int dequeue(queue *q) {
    if (q == NULL) {
        return -1;
    }

    if (queue_empty(q)) {
        printf("dequeue failed, queue is empty\n");
        return -1;
    }
    int data = q->data[q->head];
    q->head = (q->head+1)%(q->capacity);

    return data;
}

void dump(queue *q) {
    if (queue_empty(q)) {
        printf("dump failed, queue is empty\n");
        return;
    }

    for (int i = q->head; i != q->tail; i = (i+1)%(q->capacity)) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main() {
    queue *q = create_queue(5);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);

    dequeue(q);

    enqueue(q, 5);

    dump(q);
    printf("----------------------\n");
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dump(q);
    

    return 0;
}