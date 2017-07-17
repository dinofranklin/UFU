#ifndef STACK_H
#define STACK_H

typedef struct stacknode{
    char name;
    struct stacknode *next;
}StackNode;

typedef struct stack{
    int size;
    StackNode *top;
    StackNode *bot;
}Stack;

Stack *make_stack();

void push(Stack *s, char name);

void pop(Stack *s);

char top(Stack *s);

void destroy_stack(Stack *s);

void show_stack(Stack *s);

#endif
