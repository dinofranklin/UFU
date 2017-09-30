#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define or ||
#define not !
#define and &&

Graph *make_graph(int vert){
    if(vert <= 0) return NULL;

    int i, j;
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if(g == NULL) return g;

    g->n_vert = vert;
    g->n_edge = 0;
    g->degree = (int *) calloc(vert,sizeof(int));
    if(g->degree == NULL){  
        free(g);
        return NULL;
    }

    g->edges = (int **) calloc(vert,sizeof(int *));
    if(g->edges == NULL){
        free(g->degree);
        free(g);
        return NULL;
    }

    for(i=0; i<vert; ++i){
        g->edges[i] = (int *) calloc(vert, sizeof(int));
        if(g->edges[i] == NULL){
            for(j=0; j<i; ++j){
                free(g->edges[j]);
            }
            free(g->degree);
            free(g);
        }
    }
    return g;
}

void print_adjacency(Graph *g, int v){
    int i, c;
    if(g == NULL or v<0 or v>=g->n_vert){
        printf("Grafo inexistente ou vertice invalido!\n");
    }
    else{
        c = 0;
        for(i=0; i<g->n_vert; ++i){
            if(g->edges[v][i]){
                printf("%d -> %d = %d\n", v, i, g->edges[v][i]);
                c++;
            }
        }
        if(not c){
            printf("O vertice %d nao possui vertices adjacentes\n", v);
        }
    }
    return;
}

void print_graph(Graph *g){
    int i, j;
    if(g == NULL){
        printf("Grafo inexistente\n");
        return;
    }
    else if(not g->n_edge){
        printf("Grafo vazio\n");
        return;
    }
    printf("Nro de vertices: %d\n", g->n_vert);
    printf("Nro de arestas: %d\n", g->n_edge);
    printf("Graus dos vertices:\n");
    for(i=0; i<g->n_vert; ++i){
        printf("%d ", g->degree[i]);
    }
    printf("\nAdjacencias dos vertices:\n");
    for(i=0; i<g->n_vert; ++i){
        print_adjacency(g, i);
    }
    return;
}

int insert_edge(Graph *g, int v1, int v2, int weight){
    
    if(g==NULL or v1>=g->n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }
    
    else if(g->edges[v1][v2]){
        return 0;
    }   

    g->edges[v1][v2] = weight;
    g->n_edge++;
    g->degree[v1]++;
    g->degree[v2]++;
    return 1;
}

int verify_edge(Graph *g, int v1, int v2){
    
    if(g==NULL or v1>=g->n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }

    else if(g->edges[v1][v2]){
        return 1;
    }
    return 0;
}

int remove_edge(Graph *g, int v1, int v2){
    
    if(g==NULL or v1>g->=n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }

    else if(not(g->edges[v1][v2])){
        return 0;
    }

    g->edges[v1][v2] = 0;
    g->n_edge--;
    g->degree[v1]--;
    g->degree[v2]--;
    return 1;
}

int consult_edge(Graph *g, int v1, int v2, int *p){

    if(g==NULL or v1=>g->n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }
    
    else if(g->edges[v1][v2]){
        *p = g->edges[v1][v2];
        return 1;
    }
    *p = 0;
    return 0;
}

void free_graph(Graph **g){
    int i, j;
    for(i=0; i<(*g)->n_vert; ++i){
        free((*g)->edges[i]);
    }
    free((*g)->edges);
    free((*g)->degree);
    free((*g));
    *g = NULL;
    return;
}