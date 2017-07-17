#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"

CQueue *make_cqueue(){
    CQueue *cq = (CQueue *) malloc(sizeof(CQueue));
    cq->size = 0;
    cq->last = NULL;
    cq->current = NULL;
    return cq;
}

void enqueue(CQueue *cq, char name[]){
    int i;
    Player *new = (Player *) malloc(sizeof(Player));
    strcpy(new->name, name);
    new->path = make_stack();
    for(i = 0; i < ASIZE; ++i){
        new->visited[i] = false;
    }
    if(!cq->size){
        cq->current = new;
    }
    else{
        cq->last->next = new;
    }
    cq->last = new;
    new->next = cq->current;
    ++(cq->size);
    return;
}

void dequeue(CQueue *cq){
    Player *aux = cq->current;
    if(aux == aux->next){
        cq->current = NULL;
    }
    else{
        cq->current = cq->current->next;
        cq->last->next = cq->current;
    }
    destroy_stack(aux->path);
    free(aux);
    --(cq->size);
    return;
}

void update_cqueue(CQueue *cq){
    cq->last = cq->current;
    cq->current = cq->current->next;
}

char *front(CQueue *cq){
    return cq->current->name;
}

void destroy_cqueue(CQueue *cq){
    while(cq->size){
        dequeue(cq);
    }
    free(cq);
}

void show_cqueue(CQueue *cq){
    Player *aux = cq->current;
    printf("Your Queue:\n");
    while(aux != NULL){
        printf("Player %s:\n", aux->name);
        show_stack(aux->path);
        aux = aux->next;
        if(aux == cq->current) break;
    }
    return;
}
