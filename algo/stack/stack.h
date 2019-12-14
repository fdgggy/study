/*
数组实现的顺序栈
 */
#ifndef _STACK_H
#define _STACK_H

typedef struct {
    int size;
    int top;
    int *data;
}stack;

#define stack_empty(stack) (stack->top == -1)
#define stack_full(stack) (stack->top == stack->size - 1)

#endif /* stack.h */