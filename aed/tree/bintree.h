#ifndef BINTREE_H
#define BINTREE_H

typedef struct treenode ArvBin;

ArvBin *make_empty();

ArvBin *make_tree(int data, ArvBin *left, ArvBin *right);

int empty_tree(ArvBin *a);

void free_tree(ArvBin **a);

int search(ArvBin *a, int target);

int remove_leaf(ArvBin **a, int target);

void show_tree(ArvBin *a);

int height(ArvBin *a);

ArvBin *father(ArvBin *a, int target);

#endif
