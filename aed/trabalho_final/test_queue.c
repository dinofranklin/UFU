//TESTE PARA FILA

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"

int main(){
    int n, i, j, cts;
    char c, name[30];
    CQueue *cq = make_cqueue();
    show_cqueue(cq);
    printf("How many players: ");
    scanf("%d", &n);
    for(i = 0; i < n; ++i){
        printf("Type the name %d: ", i+1);
        getchar();
        scanf("%[^\n]", name);
        enqueue(cq, name);
    }
    for(i = 0; i < n; ++i){
        printf("How many cities for %s: ", front(cq));
        scanf("%d", &cts);
        for(j = 0; j < cts; ++j){
            printf("Type city %d: ", j+1);
            getchar();
            scanf("%c", &c);
            push(cq->current->path, c);
        }
        update_cqueue(cq);
    }
    show_cqueue(cq);
    destroy_cqueue(cq);
    return 0;
}
