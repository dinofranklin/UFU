#include <stdio.h>
#include <stdlib.h>
#include "pqheap.h"

PQHeap *makepqh(int n){
    PQHeap *pqh = (PQHeap *) malloc(sizeof(PQHeap));
    pqh->size = 1;
    pqh->max = n+1;
    pqh->vet = (Element *) malloc(sizeof(Element)*(n+1));
    return pqh;
}

void insertpqh(PQHeap *pqh, int elmt, int prty){
    if(pqh->size == pqh->max) return;
    int i = pqh->size;

    if(pqh->size > 1){
        while(i > 1 && prty < pqh->vet[i/2].priority){
            pqh->vet[i] = pqh->vet[i/2];
            i = i/2;
        }
    }

    pqh->vet[i].value = elmt;
    pqh->vet[i].priority = prty;
    ++(pqh->size);
    return;
}

void removepqh(PQHeap *pqh){
    if(pqh->size == 1) return;
    int j, i = pqh->size;
    Element aux;
    --(pqh->size);

    if(pqh->size != 1){
        pqh->vet[1] = pqh->vet[i-1];
        i = 1;
        while(1){
            j = i*2;
            if(j > pqh->size-1) break;
            if(j+1 <= pqh->size-1 && pqh->vet[j].priority > pqh->vet[j+1].priority){
                ++j;
            }

            if(pqh->vet[j].priority < pqh->vet[i].priority){
                aux = pqh->vet[j];
                pqh->vet[j] = pqh->vet[i];
                pqh->vet[i] = aux;
                i = j;
            }
            else break;
        }
    }

    return;
}

int peekpqh(PQHeap *pqh){
    return pqh->vet[pqh->size-1].value;
}
