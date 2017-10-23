#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void dijkstra(Graph *g, int v, int *dist, int *path){
    int i, pos, new, w, min;
    int *seen = (int *) calloc(g->n_vert, sizeof(int));
    NodeGraph *aux;

    for(i=0; i<g->n_vert; ++i){
        dist[i] = INT_MAX;
        path[i] = -1;
    }
    dist[v] = 0;

    for(pos=v; pos != -1; pos=new){
        seen[pos] = 1;
        for(aux=g->edges[pos]; aux!=NULL; aux=aux->next){
            w = aux->weight + dist[pos];
            if(w < dist[aux->vertex]){
                dist[aux->vertex] = w;
                path[aux->vertex] = pos;
            }
        }
        new = -1;
        min = INT_MAX;
        for(i=0; i<g->n_vert; ++i){
            if((not seen[i]) and dist[i]<min){
                new = i;
                min = dist[i];
            }
        }
    }
    return;
}

void dijkstra_no(Graph *g, int v, int *dist, int *path){
    int i, pos, new, d, min;
    int *seen = (int *) calloc(g->n_vert, sizeof(int));
    NodeGraph *aux;
    for(i=0; i<g->n_vert; ++i){
        path[i] = -1;
        dist[i] = INT_MAX;
    }
    dist[v] = 0;
    for(pos=v; pos != -1; pos = new){
        seen[pos] = 1;
        for(aux=g->edges[pos]; aux!=NULL; aux=aux->next){
            d = dist[pos] + 1;
            if(dist[aux->vertex] > d){
                dist[aux->vertex] = d;
                path[aux->vertex] = pos;
            }
        }
        new = -1;
        min = INT_MAX;
        for(i=0; i<g->n_vert; ++i){
            if((not seen[i]) and dist[i] < min){
                new = i;
                min = dist[i];
            }
        }
    }
    return;
}
