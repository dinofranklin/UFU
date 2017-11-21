#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

struct treenode{
    int data;
    struct treenode *left;
    struct treenode *right;
};

ArvBin *make_empty(){
    return NULL;
}

ArvBin *make_tree(int data, ArvBin *left, ArvBin *right){
    ArvBin *a = (ArvBin *) malloc(sizeof(ArvBin));
    if(!a) return NULL;

    a->data = data;
    a->left = left;
    a->right = right;

    return a;
}

int empty_tree(ArvBin *a){
    if(!a) return 1;
    return 0;
}

void free_tree(ArvBin **a){
    if(!(*a)) return;
    free_tree(&(*a)->left);
    free_tree(&(*a)->right);
    free(*a);
    *a = NULL;
    return;
}

int search(ArvBin *a, int target){
    if(!a) return 0;
    if(a->data == target) return 1;
    if(search(a->left, target)) return 1;
    if(search(a->right, target)) return 1;
    return 0;
}

int remove_leaf(ArvBin **a, int target){
    if(!(*a)) return 0;

    if((*a)->data == target){
        if(!(*a)->left && !(*a)->right){
            free(*a);
            *a = NULL;
            return 1;
        }
        return 0;
    }

    if(remove_leaf(&(*a)->left, target)) return 1;
    if(remove_leaf(&(*a)->right, target)) return 1;
    return 0;
}

void show_tree(ArvBin *a){
    if(!a){
        printf("<>");
        return;
    }

    printf("<%d", a->data);
    show_tree(a->left);
    show_tree(a->right);
    printf(">");
}

int height(ArvBin *a){
    if(!a) return 0;
    int hl, hr;
    hl = height(a->left);
    hr = height(a->right);
    if(hl > hr) return hl+1;
    return hr+1;
}

ArvBin *father(ArvBin *a, int target){
    if(!a) return NULL;

    if(a->left->data == target || a->right->data == target){
        return a;
    }

    ArvBin *s = father(a->left, target);
    if(s) return s;
    return father(a->right, target);
}
