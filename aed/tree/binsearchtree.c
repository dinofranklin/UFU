#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binsearchtree.h"

DataSearch make_datasearch(int key, char *name, int age, double wage){
    DataSearch test;
    test.key = key;
    strcpy(test.name, name);
    if(!test.name) exit(1);
    test.age = age;
    test.wage = wage;
    return test;
}

BinSearchTree *make_binsearchtree(){
    return NULL;
}

int empty_binsearchtree(BinSearchTree *a){
    if(!a) return 1;
    return 0;
}

int ordered_insert(BinSearchTree **a, DataSearch info){
    if(!a) return 0;

    if(!(*a)){
        BinSearchTree *new = (BinSearchTree *) malloc(sizeof(BinSearchTree));
        if(!new) return 0;
        new->left = NULL;
        new->right = NULL;
        new->info = info;
        *a = new;
        return 1;
    }

    if(info.key > (*a)->info.key){
        return ordered_insert(&(*a)->right, info);
    }
    else{
        return ordered_insert(&(*a)->left, info);
    }
}

int ordered_remove(BinSearchTree **a, int key){
    if(!a || !(*a)) return 0;

    if(key > (*a)->info.key){
        return ordered_remove(&(*a)->right, key);
    }
    else if(key < (*a)->info.key){
        return ordered_remove(&(*a)->left, key);
    }

    //LEAF
    if(!(*a)->left && !(*a)->right){
        free(*a);
        *a = NULL;
        return 1;
    }

    //ONE SON
    else if((*a)->left && !(*a)->right){
        BinSearchTree *aux = *a;
        *a = (*a)->left;
        free(aux);
        return 1;
    }
    else if((*a)->right && !(*a)->left){
        BinSearchTree *aux = *a;
        *a = (*a)->right;
        free(aux);
        return 1;
    }

    //TWO SONS
    else{
        BinSearchTree *aux = (*a)->left;
        while(aux->right != NULL){
            aux = aux->right;
        }
        (*a)->info = aux->info;
        return ordered_remove(&(*a)->left, aux->info.key);
    }
}

int ordered_search(BinSearchTree *a, int key){
    if(!a) return 0;

    if(key == a->info.key) return 1;
    if(key >  a->info.key){
        return ordered_search(a->right, key);
    }
    else{
        return ordered_search(a->left, key);
    }
}

void show_binsearchtree(BinSearchTree *a){
    if(!a){
        printf("<>");
        return;
    }
    printf("<%d", a->info.key);
    show_binsearchtree(a->left);
    show_binsearchtree(a->right);
    printf(">");
    return;
}

void show_ordered(BinSearchTree *a){
    if(!a) return;
    
    show_ordered(a->left);
    printf("%d ", a->info.key);
    show_ordered(a->right);
    return;
}

void free_binsearchtree(BinSearchTree **a){
    if(!(*a)) return;
    free_binsearchtree(&(*a)->left);
    free_binsearchtree(&(*a)->right);
    free(*a);
    *a = NULL;
    return;
}
