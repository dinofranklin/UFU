#ifndef PQHEAP_H
#define PQHEAP_H

typedef struct element{
    int value;
    int priority;
}Element;

typedef struct pqheap{
    int size;
    int max;
    Element *vet;
}PQHeap;

PQHeap *makepqh(int n);

void insertpqh(PQHeap *pqh, int elmt, int prty);

void removepqh(PQHeap *pqh);

int peekpqh(PQHeap *pqh);

void printvet(PQHeap *pqh);

#endif
