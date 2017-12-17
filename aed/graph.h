#ifndef GRAPH_H
#define GRAPH_H

struct connection{
    int travel_time;
    int vertex;
    char *line;
    struct connection *next;
};

struct station{
    int id;
    int wait_time;
    char *name;
    struct connection *connections;
};

typedef struct station Station;

typedef struct connection Connection;

typedef struct graph Graph;

Graph *make_graph(int max_nodes);

int insert_station(Graph *g, int id, int wait_time, char *name);

int insert_connection(Graph *g, int v1, int v2, char *line, int travel_time);

int remove_connection(Graph *g, int v1, int v2);

int remove_station(Graph *g, int v);

int verify_connection(Graph *g, int v1, int v2);

int traveltime_connection(Graph *g, int v1, int v2);

void free_graph(Graph **g); 

void print_adjacency(Graph *g, int v);

void print_graph(Graph *g);

int added_vertex(Graph *g);

int degree_of(Graph *g, int v);

int reachable(Graph *g, int v, int min);

int optimal_travel(Graph *g, char *v1, char *v2);

int stations_travel(Graph *g, int n, char **names);

int dijkstra(Graph *g, int vi, int vf, int *dist, int *path);

void dijkstra_path(Graph *g, int v, int *path, int *dist, int inc);

#endif