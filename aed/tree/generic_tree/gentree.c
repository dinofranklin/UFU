#include <stdio.h>
#include <stdlib.h>
#include "gentree.h"

struct gennode{
    int data;
    struct gennode *son;
    struct gennode *brother;
};

GenTree *make_tree(int data){
    GenTree *new = (GenTree *) malloc(sizeof(GenTree));
    if(!new) return NULL;

    new->data = data;
    new->son = NULL;
    new->brother = NULL;

    return new;
}

int insert_gen(GenTree *a, GenTree *s){
    if(!a) return 0;
    if(!s) return 0;

    s->brother = a->son;
    a->son = s;
    return 1;
}

void show_gentree(GenTree *a){
    if(!a){
        printf("<>");
        return;
    }
    printf("<%d", a->data);
    show_gentree(a->son);
    printf(">");
    show_gentree(a->brother);
    return;
}

int search_gen(GenTree *a, int target){
    if(!a) return 0;

    if(a->data == target){
        return 1;
    }
    if(search_gen(a->son, target)) return 1;
    if(search_gen(a->brother, target)) return 1;
    return 0;
}

void free_gen(GenTree **a){
    if(!(*a)) return;
    free_gen(&(*a)->son);
    free_gen(&(*a)->brother);
    free(*a);
    *a = NULL;
    return;
}

int height_gen(GenTree *a){
    if(!a) return 0;
    int hs, hb;
    hs = height_gen(a->son) + 1;
    hb = height_gen(a->brother);
    if(hs>hb) return hs;
    return hb;
}
