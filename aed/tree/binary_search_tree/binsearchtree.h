#ifndef BINSEARCHTREE
#define BINSEARCHTREE

struct datasearch{
    int key;
    char name[100];
    int age;
    double wage;
};

struct nodesearch{
    struct datasearch info;
    struct nodesearch *left;
    struct nodesearch *right;
};

typedef struct datasearch DataSearch;

typedef struct nodesearch BinSearchTree;

DataSearch make_datasearch(int key, char *name, int age, double wage);

BinSearchTree *make_binsearchtree();

int empty_binsearchtree(BinSearchTree *a);

int ordered_insert(BinSearchTree **a, DataSearch info);

int ordered_remove(BinSearchTree **a, int key);

int ordered_search(BinSearchTree *a, int key);

void show_binsearchtree(BinSearchTree *a);

void show_ordered(BinSearchTree *a);

void free_binsearchtree(BinSearchTree **a);

#endif
