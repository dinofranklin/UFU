#ifndef LISTADJ_H
#define LISTADJ_H

typedef struct node{
    int vertex;
    int weight;
    struct node *next;
}Node;

typedef struct graph{
    int n_vert, n_edge;
    int *degree;
    Node **edges;
}Graph;

Graph* make_graph(int v);

int insert_edge(Graph *g, int v1, int v2, int wei);

int verify_edge(Graph *g, int v1, int v2);

int remove_edge(Graph *g, int v1, int v2);

int consult_edge(Graph *g, int v1, int v2, int *wei);

void print_adjacency(Graph *g, int v);

void print_graph(Graph *g);

void free_graph(Graph **g);

#endif