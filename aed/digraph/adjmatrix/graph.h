#ifndef MATRIZADJ_H
#define MATRIZADJ_H

typedef struct graph{
    int n_vert, n_edge;
    int *degree;
    int **edges;
}Graph;

Graph *make_graph(int vert);

void print_adjacency(Graph *g, int v);

void print_graph(Graph *g);

int insert_edge(Graph *g, int v1, int v2, int weight);

int verify_edge(Graph *g, int v1, int v2);

int remove_edge(Graph *g, int v1, int v2);

int consult_edge(Graph *g, int v1, int v2, int *p);

void free_graph(Graph **g);

#endif