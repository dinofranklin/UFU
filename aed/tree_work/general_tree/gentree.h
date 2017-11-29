#ifndef GENTREE_H
#define GENTREE_H

typedef struct gentree GenTree;

GenTree *make_gentree(int value);

int insertson_gentree(GenTree *t, GenTree *s);

int insertfather_gentree(GenTree **t, GenTree *s);

int insertnode_gentree(GenTree *t, GenTree *s, int value);

int remove_gentree(GenTree **t, int value);

void show_gentree(GenTree *t);

int search_gentree(GenTree *t, int target);

void free_gentree(GenTree **t);

int height_gentree(GenTree *t);

void print_treeview(GenTree *t, int spc);

int count_nodes(GenTree *t);

void pre_order(GenTree *t);

void post_order(GenTree *t);

void traverse_level(GenTree *t);

int leafs(GenTree *t);

int gentree_degree(GenTree *t);

int nodes(GenTree *t, int degree);

int node_height(GenTree *t, int value);

#endif
