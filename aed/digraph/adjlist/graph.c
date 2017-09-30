#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define or ||
#define not !
#define and &&

Graph *make_graph(int v){
    if(v <= 0){
        return NULL;
    }

    Graph *g = (Graph *) malloc(sizeof(Graph));
    if(g == NULL){
        return g;
    }

    int i;
    g->n_vert = v;
    g->n_edge = 0;
    g->degree = (int *) calloc(v,sizeof(int));
    if(g->degree == NULL){
        free(g);
        return NULL;
    }

    g->edges = (Node **) malloc(v*sizeof(Node *));
    if(g->edges == NULL){
        free(g->degree);
        free(g);
        return NULL;
    }
    for(i=0; i<v; ++i){
        g->edges[i] = NULL;
    }

    return g;
}

int insert_edge(Graph *g, int v1, int v2, int wei){
    if(g==NULL or v1<0 or v2<0 or v1>=g->n_vert or v2>=g->n_vert){
        return -1;
    }

    Node *aux = g->edges[v1];
    while(aux != NULL and aux->vertex != v2){
        aux = aux->next;
    }
    if(aux != NULL){
        return 0;
    }

    Node *new = (Node *) malloc(sizeof(Node));
    if(new == NULL){
        printf("Erro na alocacao de memoria\n");
        return -1;
    }
    new->vertex = v2;
    new->weight = wei;
    new->next = g->edges[v1];
    g->edges[v1] = new;

    g->n_edge++;
    g->degree[v1]++;
    g->degree[v2]++;
    return 1;
}

void print_adjacency(Graph *g, int v){
    if(g == NULL or v<0 or v>=g->n_vert){
        printf("Grafo inexistente ou vertice invalido!\n");
        return;
    }
    
    Node *aux = g->edges[v];
    if(aux == NULL){
        printf("O vertice %d nao possui vertices adjacentes\n", v);
        return;
    }
    while(aux != NULL){
        printf("%d -> %d = %d\n", v, aux->vertex, aux->weight);
        aux = aux->next;
    }
    return;
}

void print_graph(Graph *g){
    if(g == NULL){
        printf("Grafo inexistente!\n");
        return;
    }
    else if(not g->n_edge){
        printf("Grafo vazio!\n");
        return;
    }

    int i;
    printf("Nro. de vertices: %d\n", g->n_vert);
    printf("Nro. de arestats: %d\n", g->n_edge);
    printf("Graus do vertices:\n");
    for(i=0; i<g->n_vert; ++i){
        printf("%d ", g->degree[i]);
    }
    printf("\nAdjacencia dos vertices:\n");
    for(i=0; i<g->n_vert; ++i){
        print_adjacency(g, i);
    }
    return;
}

int verify_edge(Graph *g, int v1, int v2){
    if(g==NULL or v1>=g->n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }
    
    Node *aux = g->edges[v1];
    while(aux != NULL and aux->vertex != v2){
        aux = aux->next;
    }

    if(aux == NULL){
        return 0;
    }
    return 1;
}

int remove_edge(Graph *g, int v1, int v2){
    if(g==NULL or v1>=g->n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }

    Node *aux, *prv;
    aux = g->edges[v1];
    prv = NULL;
    while(aux != NULL and aux->vertex != v2){
        prv = aux;
        aux = aux->next;
    }
    
    if(aux == NULL){
        return 0;
    }
    if(prv == NULL){
        g->edges[v1] = aux->next;
    }
    else{
        prv->next = aux->next;
    }

    free(aux);
    g->n_edge--;
    g->degree[v1]--;
    g->degree[v2]--;
    return 1;
}

int consult_edge(Graph *g, int v1, int v2, int *wei){
    if(g==NULL or v1>=g->n_vert or v2>=g->n_vert or v1<0 or v2<0){
        return -1;
    }

    Node *aux = g->edges[v1];
    while(aux != NULL and aux->vertex != v2){
        aux = aux->next;
    }

    if(aux==NULL){
        *wei = 0;
        return 0;
    }
    else{
        *wei = aux->weight;
        return 1;
    }
}

void free_graph(Graph **g){
    if(*g == NULL) return;

    int i;
    Node *aux, *tmp;
    for(i=0; i<(*g)->n_vert; ++i){
        tmp = (*g)->edges[i];
        while(tmp != NULL){
            aux = tmp;
            tmp = tmp->next;
            free(aux);
        }
    }
    
    free((*g)->edges);
    free((*g)->degree);
    free(*g);
    *g = NULL;
    return;
}