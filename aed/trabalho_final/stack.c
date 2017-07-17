#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *make_stack(){
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->size = 0;
    s->top = NULL;
    s->bot = NULL;
    return s;
}

void push(Stack *s, char name){
    StackNode *new = (StackNode *) malloc(sizeof(StackNode));
    new->name = name;
    if(!s->size){
        new->next = NULL;
        s->bot = new;
    }
    else{
        new->next = s->top;
    }
    s->top = new;
    ++(s->size);
    return;
}

void pop(Stack *s){
    StackNode *aux;
    aux = s->top;
    if(s->top == s->bot){
        s->bot = NULL;
    }
    s->top = s->top->next;
    free(aux);
    --(s->size);
    return;
}

char top(Stack *s){
    return s->top->name;
}

void destroy_stack(Stack *s){
    while(s->size){
        pop(s);
    }
    free(s);
    return;
}

void show_stack(Stack *s){
    StackNode *cur;
    cur = s->top;
    printf("Player Stack:\n[");
    while(cur != NULL){
        printf(" %c", cur->name);
        cur = cur->next;
    }
    printf(" ]\n");
    return;
}
