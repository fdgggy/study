/*
出栈时间复杂度是O(1),入栈时间复杂度最好情况是O(1),最坏是O(n)
应用：
1.函数调用
2.表达式求值  1+2*3
3.括号匹配   {[()]}
4.浏览器前进后退。用两个栈.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./stack.h"

stack *create_stack(int size) {
    stack *s = (stack*)malloc(sizeof(stack));
    if (s == NULL) {
        return NULL;
    }
    s->size = size;
    s->top = -1;
    s->data = (int*)malloc(sizeof(int)*size);
    if (s->data == NULL) {
        free(s->data);
        return NULL;
    }
    return s;
}

void destroy(stack *s) {
    if (NULL == s) {
        return;
    }
    if (s->data != NULL) {
        free(s->data);
    }
    free(s);

    return;
}

//支持动态扩容的顺序栈
void push_ex(stack *s, int data) {
    if (NULL == s) {
        printf("push_ex failed, stack is null\n");
        return;
    }

    if (stack_full(s)) {
        printf("stack_full is full, size:%d\n", s->size);
        int new_size = (s->size)*2;
        int *d = (int*)malloc(sizeof(int)*new_size);
        if (NULL == d) {
            return;
        }
        memmove(d, s->data, s->size*sizeof(int));  //一定要注意是移动单位是字节，不是元素个数, 注意和memcpy的区别

        free(s->data);

        s->data = d;
        s->size = new_size;
    }
    s->top++;
    s->data[s->top] = data;
}

void push(stack *s, int data) {
    if (NULL == s) {
        printf("push failed, stack is null\n");
        return;
    }
    if (stack_full(s)) {
        printf("stack is full\n");
        return;
    }

    s->top++;
    s->data[s->top] = data;
    // s->data[s->top++] = data;   //错误的
}

void pop(stack *s) {
    if (NULL == s) {
        printf("pop failed, stack is null\n");
        return;
    }
    if (stack_empty(s)) {
        printf("stack is empty\n");
        return;
    }
    int data = s->data[s->top];
    s->top--;
    printf("pop data:%d\n", data);
}

void dump(stack *s) {
    for (int i = s->top; i >= 0; i--) {
        printf("index:%d data:%d\n", i, s->data[i]);
    }
}

int main() {
    stack *s = create_stack(3);
    push_ex(s, 1);
    push_ex(s, 2);
    push_ex(s, 3);
    // dump(s);
    push_ex(s, 4);
    push_ex(s, 5);
    push_ex(s, 6);
    push_ex(s, 7);

    dump(s);
    printf("stack size:%d\n", s->size);

    // printf("--------------------\n");
    // pop(s);
    // dump(s);
    // printf("--------------------\n");
    // pop(s);
    // dump(s);
    // printf("--------------------\n");
    // pop(s);
    // dump(s);
    // printf("--------------------\n");
    // pop(s);
    // dump(s);
    destroy(s);

    int v = 5;
    int *p = NULL;
    int *q = NULL;

    assert(p != NULL || q != NULL);  //计算括号内的表达式，如果表达式为false(0)，报告错误，并终止
    printf("p!=NULL\n");

    return 0;
}
