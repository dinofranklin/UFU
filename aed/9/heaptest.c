#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pqheap.h"

int main(){
    int n, i, r;
    clock_t ti, tf;
    double t;
    printf("Digite o numero de elementos da fila: ");
    scanf("%d", &n);
    PQHeap *pqh = makepqh(n);
    srand(time(NULL));
    printf("Tempo gasto para inserir %d elementos na fila de prioridade com heap\n", n);

    //Inserção em ordem ascendente.
    ti = clock();
    for(i = 0; i < n; ++i){
        insertpqh(pqh, 1, i);
    }
    tf = clock();
    t = ((double) (tf-ti))/CLOCKS_PER_SEC;
    printf("Ordem ascendente com %d elementos: %.8lfs\n", n, t);
    for(i = 0; i < n; ++i){
        removepqh(pqh);
    }

    //Inserção em ordem decrescente.
    ti = clock();
    for(i = n; i > 0; --i){
        insertpqh(pqh, 1, i);
    }
    tf = clock();
    t = ((double) (tf-ti))/CLOCKS_PER_SEC;
    printf("Ordem decrescente com %d elementos: %.8lfs\n", n, t);
    for(i = 0; i < n; ++i){
        removepqh(pqh);
    }

    //Inserção em ordem aleatória.
    ti = clock();
    for(i = 0; i < n; ++i){
        r = rand()%n;
        insertpqh(pqh, 1, r);
    }
    tf = clock();
    t = ((double) (tf-ti))/CLOCKS_PER_SEC;
    printf("Ordem aleatoria com %d elementos: %.8lfs\n", n, t);

    return 0;
}
