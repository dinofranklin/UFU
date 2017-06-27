#ifndef PRIORITYQ_H
#define PRIORITYQ_H

typedef struct element{
    int value;
    int priority;
}Element;

typedef struct{
    int size;
    int max;
    Element *vet;
}PriorityQ;

PriorityQ* makepq(int n);

void insertpq(PriorityQ* pq, int elmt, int prty);

void removepq(PriorityQ* pq);

int peekpq(PriorityQ* pq);

#endif
