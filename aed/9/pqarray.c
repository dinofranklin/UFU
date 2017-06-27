#include <stdio.h>
#include <stdlib.h>
#include "pqarray.h"

PriorityQ* makepq(int n){
    PriorityQ *pq = (PriorityQ *) malloc(sizeof(PriorityQ));
    pq->size = 0;
    pq->max = n;
    pq->vet = (Element *) malloc(sizeof(Element)*n);
    return pq;
}

void insertpq(PriorityQ* pq, int elmt, int prty){
    if(pq->max == pq->size) return;
    int i = pq->size;

    if(pq->size){
        while(i-1 >= 0 && prty <= pq->vet[i-1].priority){
            pq->vet[i] = pq->vet[i-1];
            --i;
        }
    }

    pq->vet[i].value = elmt;
    pq->vet[i].priority = prty;

    ++(pq->size);
    return;
}

void removepq(PriorityQ* pq){
    if(pq->size == 0) return;
    --(pq->size);
    return;
}

int peekpq(PriorityQ* pq){
    int i = pq->size;
    return pq->vet[i].value;
}
