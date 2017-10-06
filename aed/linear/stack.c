#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define or ||
#define not !
#define and &&

Stack* make_stack(){
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->size = 0;
    s->top = NULL;
    return s;
}

void push(Stack *s, int val){
    StackNode *new = (StackNode *) malloc(sizeof(StackNode));
    new->data = val;

    if(not s->size){
        new->next = NULL;
    }
    else{
        new->next = s->top;
    }
    s->top = new;
    s->size++;
    return;
}

void pop(Stack *s){
    StackNode *aux = s->top;
    s->top = s->top->next;
    free(aux);
    s->size--;
    return;
}

int empty_stack(Stack *s){
    return s->size == 0;
}

int top(Stack *s){
    return s->top->data;
}
