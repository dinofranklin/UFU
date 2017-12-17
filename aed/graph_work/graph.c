#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "graph.h"

#define and &&
#define not !
#define or ||

struct graph{
    int max_nodes;
    int added_nodes;
    Station **stations;
};

//MAKES A GRAPH.
Graph *make_graph(int max_nodes){
    
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if(not g) return NULL;

    g->max_nodes = max_nodes;
    g->added_nodes = 0;
    g->stations = (Station **) malloc(max_nodes * sizeof(Station *));

    if(not g->stations){
        free(g);
        return NULL;
    }

    int i;
    for(i=0; i<max_nodes; ++i){
        g->stations[i] = NULL;
    }

    return g;
}



//MAKES A STATION.
Station *make_station(int id, int wait_time, char *name){
    
    Station *new = (Station *) malloc(sizeof(Station));
    if(not new) return NULL;

    new->id = id;
    new->wait_time = wait_time;
    new->connections = NULL;

    new->name = (char *) malloc(strlen(name) * sizeof(char));
    if(not new->name){
        free(new);
        return NULL;
    }

    strcpy(new->name, name);
    return new;
}



//INSERTS A STATION ON THE GRAPH.
int insert_station(Graph *g, int id, int wait_time, char *name){
    
    if(not g or id < 0 or id >= g->max_nodes or wait_time < 0) return -1;

    if(g->stations[id]) return 0;

    Station *e = make_station(id, wait_time, name);
    if(not e) return -1;

    g->stations[id] = e;
    g->added_nodes++;
    return 1;
}



//MAKES A CONNECTION.
Connection *make_connection(int v, char *line, int travel_time){
    
    Connection *new = (Connection *) malloc(sizeof(Connection));
    if(not new) return NULL;

    new->travel_time = travel_time;
    new->vertex = v;
    new->next = NULL;
    new->line = line;

    return new;
}


//INSERTS A CONNECTION BETWEEN TWO STATIONS.
int insert_connection(Graph *g, int v1, int v2, char *line, int travel_time){
    if(not g or v1<0 or v2<0 or v1>=g->max_nodes or v2>=g->max_nodes or travel_time<0){
        return -1;
    }

    if(not g->stations[v1] or not g->stations[v2]){
        return -1;
    }

    if(verify_connection(g, v1, v2) == 1){
        return 0;
    }

    char *newline = (char *) malloc(strlen(line)*sizeof(char));
    if(not newline) return -1;
    strcpy(newline, line);

    Connection *c1, *c2;
    c1 = make_connection(v2, newline, travel_time);
    if(not c1){
        free(newline);
        return -1;
    }

    c2 = make_connection(v1, newline, travel_time);
    if(not c2){
        free(newline);
        free(c1);
        return -1;
    }

    c1->next = g->stations[v1]->connections;
    g->stations[v1]->connections = c1;

    c2->next = g->stations[v2]->connections;
    g->stations[v2]->connections = c2;
    return 1;    
}



//REMOVES A CONNECTION BETWEEN TWO STATIONS.
int remove_connection(Graph *g, int v1, int v2){
    if(not g or v1<0 or v2<0 or v1>=g->max_nodes or v2>=g->max_nodes){
        return -1;
    }

    if(not g->stations[v1] or not g->stations[v2]){
        return -1;
    }

    Connection *cur, *aux;
    aux = NULL;
    for(cur = g->stations[v1]->connections; cur != NULL; cur = cur->next){
        if(cur->vertex == v2){
            break;
        }
        aux = cur;
    }

    if(not cur) return 0;
    if(aux) aux->next = cur->next;
    else g->stations[v1]->connections = cur->next;

    free(cur->line);
    free(cur);
    
    aux = NULL;
    for(cur = g->stations[v2]->connections; cur != NULL; cur = cur->next){
        if(cur->vertex == v1){
            break;
        }
        aux = cur;
    }

    if(not cur) return 0;
    if(aux) aux->next = cur->next;
    else g->stations[v2]->connections = cur->next;

    free(cur->line);
    free(cur);

    return 1;
}



//REMOVES A STATION.
int remove_station(Graph *g, int v){

    if(not g or v<0 or v>=g->max_nodes){
        return -1;
    }

    if(not g->stations[v]){
        return 0;
    }

    Connection *c;
    for(c = g->stations[v]->connections; c != NULL; c = c->next){
        remove_connection(g, v, c->vertex);    
    }

    free(g->stations[v]->name);
    free(g->stations[v]);
    g->stations[v] = NULL;
    return 1;
}



//VERIFY IF THERE IS A CONNECTION BETWEEN TWO STATIONS.
int verify_connection(Graph *g, int v1, int v2){
    if(not g or v1<0 or v2<0 or v1>=g->max_nodes or v2>=g->max_nodes){
        return -1;
    }

    if(not g->stations[v1] or not g->stations[v2]){
        return -1;
    }

    Connection *c;
    for(c = g->stations[v1]->connections; c != NULL; c = c->next){
        if(c->vertex == v2){
            return 1;
        }
    }

    return 0;
}



//RETURNS THE TRAVEL TIME BETWEEN TWO STATIONS
int traveltime_connection(Graph *g, int v1, int v2){
    if(not g or v1<0 or v2<0 or v1>=g->max_nodes or v2>=g->max_nodes){
        return -1;
    }

    if(not g->stations[v1] or not g->stations[v2]){
        return -1;
    }

    Connection *c;
    for(c = g->stations[v1]->connections; c != NULL; c = c->next){
        if(c->vertex == v2){
            return c->travel_time;
        }
    }

    return -1;
}



//FREES A GRAPH.
void free_graph(Graph **g){
    if(not g or not *g) return;

    int i;
    for(int i=0; i<(*g)->max_nodes; ++i){
        Station *e =  (*g)->stations[i];
        if(not e) continue;
        Connection *c, *aux;

        c = e->connections;
        aux = NULL;
        while(c != NULL){
            aux = c;
            c = c->next;

            free(aux->line);
            free(aux);
        }

        free(e->name);
        free(e);
    }

    free((*g)->stations);
    free(*g);
    *g = NULL;
}



//PRINTS THE ADJACENCY OF A VERTEX.
void print_adjacency(Graph *g, int v){
    if(not g or v < 0 or v >= g->max_nodes){
        printf("ERROR: INVALID VERTEX!\n");
        return;
    }

    if(not g->stations[v]){
        printf("Station %d has not been added yet.\n", v);
        return;
    }

    Station *e = g->stations[v];
    printf("Station %d - %s - W.T: %d min. Can travel to:\n", v, e->name, e->wait_time);
    if(not g->stations[v]->connections){
        printf("Station %d has no adjacency.\n", v);
        return;
    }

    Connection *c = e->connections;
    while(c != NULL){
        printf("\t%d on %s line taking %d min\n", c->vertex, c->line, c->travel_time);
        c = c->next;
    }
    return;
}



//PRINTS THE GRAPH.
void print_graph(Graph *g){
    if(not g) return;
    
    int i;
    for(i=0; i<g->max_nodes; ++i){
        print_adjacency(g, i);
    }
    return;
}



//RETURNS THE NUMBER OF ADDED VERTEX;
int added_vertex(Graph *g){
    if(not g) return -1;

    return g->added_nodes;
}



//GETS THE DEGREE OF A VERTEX.
int degree_of(Graph *g, int v){
    if(not g or v<0 or v>=g->max_nodes or not g->stations[v]){
        return -1;
    }

    int cnt = 0;
    Connection *c;
    for(c = g->stations[v]->connections; c!=NULL; c=c->next){
        ++cnt;
    }

    return cnt;
}



//DIJKSTRA.
int dijkstra(Graph *g, int vi, int vf, int *dist, int *path){
    if(not g or vi>=g->max_nodes or vi<0 or not dist or not path){
        return -1;
    }

    int i, j, *seen;
    char **line;
    seen = (int *) malloc(g->max_nodes * sizeof(int));
    line = (char **) malloc(g->max_nodes * sizeof(char *));

    for(i=0; i<g->max_nodes; ++i){
        dist[i] = INT_MAX;
        path[i] = -1;
        seen[i] = 0;
        line[i] = NULL;
    }

    int dmin, vmin, calcd;
    dist[vi] = 0;
    Connection *cnx;

    for(i=vi; i!=-1; i=vmin){

        seen[i] = 1;
        if(i == vf) break;

        for(cnx = g->stations[i]->connections; cnx != NULL; cnx = cnx->next){
            
            if(seen[cnx->vertex]) continue;
            calcd = cnx->travel_time + dist[i];
            if(line[i] == NULL or strcmp(line[i], cnx->line)){
                calcd += g->stations[i]->wait_time;
            }

            if(calcd < dist[cnx->vertex]){
                line[cnx->vertex] = cnx->line;
                dist[cnx->vertex] = calcd;
                path[cnx->vertex] = i;
            }
        }

        vmin = -1;
        dmin = INT_MAX;
        for(j=0; j<g->max_nodes; ++j){
            if(seen[j]) continue;
            if(dist[j] < dmin){
                dmin = dist[j];
                vmin = j;
            }
        }
    }

    if(dist[vf] != INT_MAX) return 1;
    free(line);
    free(seen);
    return 0;
}



//PRINTS THE DIJKSTRA PATH.
void dijkstra_path(Graph *g, int v, int *path, int *dist, int inc){
    if(path[v] != -1){
        dijkstra_path(g, path[v], path, dist, inc);
    }
    printf("\n%02d, %-20s - %03d minutes taken-> ", v, g->stations[v]->name, dist[v]+inc);
    return;
}



//PRINTS THE OPTIMAL PATH CALCULATED BY DIJKSTRA.
int optimal_travel(Graph *g, char *v1, char *v2){
    if(not g or not v1 or not v2) return -1;
    
    int i, beg, end;
    beg = end = -1;

    for(i=0; i<g->max_nodes; ++i){
        if(beg == -1 && not strcmp(v1, g->stations[i]->name)){
            beg = i;
            if(end != -1) break;
        }
        if(end == -1 && not strcmp(v2, g->stations[i]->name)){
            end = i;
            if(beg != -1) break;
        }
    }

    if(beg == -1 or end == -1 or beg == end) return 0;

    int *path, *dist;
    path = (int *) malloc(g->max_nodes*sizeof(int));
    dist = (int *) malloc(g->max_nodes*sizeof(int));

    int res = dijkstra(g, beg, end, dist, path);
    if(res == -1) return -1;
    if(not res) return 0;
    
    printf("\nOptimal path between %s and %s:\n", v1, v2);
    dijkstra_path(g, end, path, dist, 0);
    printf("\b\b\b   \n\nTotal time taken: %d min.\n\n", dist[end]);

    free(path);
    free(dist);
    return 1;
}



//GETS A LIST OF STATIONS AND PRINTS THE TRIP.
int stations_travel(Graph *g, int n, char **names){
    if(not g or n<0 or n>g->added_nodes or not names){
        return -1;
    }
    
    bool found;
    int i, j, *verts;
    verts = (int *) malloc(g->max_nodes*sizeof(int));
    int start, vmin, dmin, totaltime;
    start = -1;

    for(i=0; i<g->max_nodes; ++i) verts[i] = -1;

    for(i=0; i<n; ++i){
        found = false;
        for(j=0; j<g->max_nodes; ++j){
            if(not g->stations[j]) continue;

            if(not strcmp(g->stations[j]->name, names[i])){
                verts[g->stations[j]->id] = 0;
                if(start == -1) start = g->stations[j]->id;
                found = true;
                break;
            }
        }
        if(not found){
            free(verts);
            return -1;
        }
    }

    int *path, *dist;
    path = (int *) malloc(g->max_nodes*sizeof(int));
    dist = (int *) malloc(g->max_nodes*sizeof(int));
    totaltime = 0;

    while(start != -1){
        verts[start] = 1;
        dijkstra(g, start, -1, dist, path);
        
        vmin = -1;
        dmin = INT_MAX;

        for(i=0; i<g->max_nodes; ++i){

            if(not verts[i] && dist[i] < dmin){
                dmin = dist[i];
                vmin = i;
            }
        }
        if(vmin == -1) break;
        dijkstra_path(g, vmin, path, dist, totaltime);
        totaltime += dmin;
        start = vmin;
    }

    printf("\n\nTotal time taken: %d min\n", totaltime);
    return 1;
}



//DFS GRAPH TRAVERSAL.
void dfs(Graph *g, int v, int min, char *line, int *seen){
    if(not g->stations[v] or not g->stations[v]->connections or seen[g->stations[v]->id] or min <= 0){
        return;
    }

    int vt, t;
    seen[v] = 1;
    Connection *c;

    for(c=g->stations[v]->connections; c!=NULL; c=c->next){
        vt = c->vertex;
        if(seen[vt]) continue;
        t = c->travel_time;
        if(line == NULL or not strcmp(line, c->line)) t += g->stations[v]->wait_time;

        if(min - t >= 0){
            printf("%d, ", vt);
            dfs(g, vt, min-t, c->line, seen);
        }
    }
    
    return;
}



//PRINTS THE REACHABLE STATIONS WITHIN A TIME.
int reachable(Graph *g, int v, int min){
    if(not g or v<0 or v>=g->max_nodes or not g->stations[v]){
        return -1;
    }

    int *seen = (int *) calloc(g->max_nodes, sizeof(int));
    printf("\nStations reachable from %d taking at max %d min:\n", v, min);
    dfs(g, v, min, NULL, seen);
    printf("\b\b  \n\n");
    return 1;
}