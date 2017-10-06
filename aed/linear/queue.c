#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define or ||
#define not !
#define and &&

Queue *make_queue(){
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->size = 0;
    q->front = NULL;
    q->back = NULL;
    return q;
}

void enqueue(Queue *q, int v){
    QueueNode *new = (QueueNode *) malloc(sizeof(QueueNode));
    new->data = v;
    new->next = NULL;

    if(not q->front){
        q->front = new;
    }
    else{
        q->back->next = new;
    }
    q->back = new;
    q->size++;
    return;
}

void dequeue(Queue *q){
    QueueNode *aux = q->front;

    if(not q->size){
        q->back = NULL;
        q->front = NULL;
    }
    else{
        q->front = q->front->next;
    }
    free(aux);
    q->size--;
    return;
}

int front(Queue *q){
    return q->front->data;
}

int empty_queue(Queue *q){
    return q->size == 0;
}