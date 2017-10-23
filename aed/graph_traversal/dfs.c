#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void DFS(Graph *g){

    int i, j;
    int *seen = (int *) calloc(1+g->n_vert, sizeof(int));
    for(i=1; i<=g->n_vert; ++i){
        dfs_recursive(g, seen, i);
        if(i != g->n_vert){
            for(j=1; j<=g->n_vert; ++j) seen[j] = 0;
        }
    }

    return;
}

void dfs_recursive(Graph *g, int *seen, int v){
    int i, vt;
    NodeGraph *aux = g->edges[v];
    seen[v] = 1;
    for(aux=g->edges[v]; aux != NULL; aux=aux->next){
        vt = aux->vertex;
        if(not seen[vt]){
            dfs_recursive(g,seen,vt);
        }
    }
    return;
}

void dfs_iterative(Graph *g, int v){
    int vt, val;
    int *seen;
    seen = (int *) calloc(g->n_vert,sizeof(int));
    Stack *s = make_stack();
    push(s, v);
    seen[v] = 1;

    while(not empty_stack(s)){
        NodeGraph *aux;
        vt = top(s);
        pop(s);
 
        for(aux=g->edges[vt]; aux!=NULL; aux=aux->next){
            val = aux->vertex;
            if(not seen[val]){
                push(s, val);
                seen[val] = 1;
            }
        }
    }
    return;
}
