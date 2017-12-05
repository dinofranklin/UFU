#ifndef AVLTREE_H
#define AVLTREE_H


//KEY = TRAFFIC.
struct netnode{
    int id;
    int traffic;
    int capacity;
    char *location;
};

typedef struct netnode NetNode;

typedef struct avltree AvlTree;

NetNode make_node(int id, int traffic, int capacity, char *location);

AvlTree *make_avltree();

int empty_avltree(AvlTree *t);

int search_avltree(AvlTree *t, int target);

void show_avl(AvlTree *t);

void ordered_avl(AvlTree *t);

void treeview_avl(AvlTree *t, int space);

void free_avl(AvlTree **t);

void print_node(NetNode n);

int rotate_right(AvlTree **t);

int rotate_left(AvlTree **t);

int balance_right(AvlTree **t);

int balance_left(AvlTree **t);

int insert_avl(AvlTree **t, NetNode n);

int remove_avl(AvlTree **t, int target);

NetNode least_traffic(AvlTree *t);

int count_idle(AvlTree *t);

int count_internal(AvlTree *t);

int check_full(AvlTree *t, int level);

int full(AvlTree *t);

int find_level(AvlTree *t, NetNode n, int level);

int level_of(AvlTree *t, NetNode n);

int equal_avl(AvlTree *t1, AvlTree *t2);


#endif