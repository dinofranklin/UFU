#ifndef STACK_H
#define STACK_H

typedef struct stacknode{
    int data;
    struct stacknode *next;
}StackNode;

typedef struct stack{
    int size;
    StackNode *top;
}Stack;

Stack* make_stack();

void push(Stack *s, int val);

void pop(Stack *s);

int empty_stack(Stack *s);

int top(Stack *s);

#endif