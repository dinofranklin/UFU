#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "stack.h"
#define ASIZE 26
#define NSIZE 30

typedef struct player{
    char name[NSIZE];
    bool visited[ASIZE];
    Stack *path;
    struct player *next;
}Player;

typedef struct cqueue{
    int size;
    Player *current;
    Player *last;
}CQueue;

CQueue *make_cqueue();

void enqueue(CQueue *cq, char name[]);

void dequeue(CQueue *cq);

void update_cqueue(CQueue *cq);

char *front(CQueue *cq);

void destroy_cqueue(CQueue *cq);

void show_cqueue(CQueue *cq);

#endif
