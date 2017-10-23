#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void BFS(Graph *g, int v){

    int *seen = (int *) calloc(g->n_vert,sizeof(int));
    Queue *q = make_queue();
    enqueue(q, v);
    seen[v] = 1;
    bfs_recursive(g, q, seen);
    return;
}

void bfs_recursive(Graph *g, Queue *q, int *seen){
    int val, vt;
    NodeGraph *aux;
    vt = front(q); 
    dequeue(q);
    for(aux=g->edges[vt]; aux != NULL; aux=aux->next){
        val = aux->vertex;
        if(not seen[val]){
            enqueue(q, val);
            seen[val] = 1;        
        }
    }
    if(not empty_queue(q)){
        bfs_recursive(g,q,seen);
    }
}

void bfs_iterative(Graph *g, int v){
    int vt, val;
    int *seen;
    seen = (int *) calloc(g->n_vert,sizeof(int));
    Queue *q = make_queue();
    enqueue(q, v);
    seen[v] = 1;
    int i;
    while(not empty_queue(q)){
        NodeGraph *aux;
        vt = front(q);
        dequeue(q);
        for(aux=g->edges[vt]; aux!=NULL; aux=aux->next){
            val = aux->vertex;
            if(not seen[val]){
                enqueue(q, val);
                seen[val] = 1;
            }
        }
    }
    return;
}
