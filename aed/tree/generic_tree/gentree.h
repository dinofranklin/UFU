#ifndef GENTREE_H
#define GENTREE_H

typedef struct gennode GenTree;

GenTree *make_tree(int data);

int insert_gen(GenTree *a, GenTree *s);

void show_gentree(GenTree *a);

int search_gen(GenTree *a, int target);

void free_gen(GenTree **a);

int height_gen(GenTree *a);

#endif
