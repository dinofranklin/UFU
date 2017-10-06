#ifndef QUEUE_H
#define QUEUE_H

typedef struct queuenode{
    int data;
    struct queuenode *next;
}QueueNode;

typedef struct queue{
    int size;
    QueueNode *back;
    QueueNode *front;
}Queue;

Queue *make_queue();

void enqueue(Queue *q, int v);

void dequeue(Queue *q);

int front(Queue *q);

int empty_queue(Queue *q);

#endif