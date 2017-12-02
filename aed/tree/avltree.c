#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "avltree.h"

#define and &&
#define not !
#define or ||


struct avltree{
    int factor;
    Info info;
    struct avltree *left;
    struct avltree *right;
};



Info make_register(int value, char *str){
    Info f;
    f.data = value;
    f.str = (char *) malloc(sizeof(char)*strlen(str));
    strcpy(f.str, str);
    
    return f;
}



AVLTree *make_avl(){
    return NULL;
}



int empty_AVL(AVLTree *t){
    if(not t) return 1;
    return 0;
}



int search_avl(AVLTree *t, int target){
    if(not t) return 0;

    if(t->info.data == target) return 1;
    if(t->info.data >= target) return search_avl(t->left, target);
    return search_avl(t->right, target);
}



void show_avl(AVLTree *t){
    if(not t){
        printf("<>");
        return;
    }
    
    printf("<%d", t->info.data);
    show_avl(t->left);
    show_avl(t->right);
    printf(">");
    
    return;
}



void free_avl(AVLTree **t){
    if(not t or not (*t)) return;
    
    free_avl(&(*t)->left);
    free_avl(&(*t)->right);
    free((*t)->info.str);
    free(*t);
    
    *t = NULL;
    return;
}

void ordered_avl(AVLTree *t){
    if(not t) return;

    ordered_avl(t->left);
    printf("%d ", t->info.data);
    ordered_avl(t->right);
    return;
}



void treeview_avl(AVLTree *t, int space){
    if(not t) return;

    int i;
    for(i=0; i<space; ++i){
        putchar(' ');
    }
    printf("|%d\n", t->info.data);
    
    treeview_avl(t->left, space+3);
    treeview_avl(t->right, space+3);
    return;
}



int insert_AVL(AVLTree **t, Info f, int *balance){
    if(not t) return 0;

    if(not (*t)){
        AVLTree* new = (AVLTree *) malloc(sizeof(AVLTree));
        new->info = f;
        new->factor = 0;
        new->left = NULL;
        new->right = NULL;

        *t = new;
        *balance = 1;
    }

    else if(f.data <= (*t)->info.data){
        insert_AVL(&(*t)->left, f, balance);
        if(*balance == 1){

            if((*t)->factor == 1){
                balance_left(t);
                *balance = 0;
            }
            else if((*t)->factor == 0){
                (*t)->factor = 1;
            }
            else{
                (*t)->factor = 0;
                *balance = 0;
            }
        }
    }

    else{
        insert_AVL(&(*t)->right, f, balance);
        if(*balance == 1){
            if((*t)->factor == -1){
                balance_right(t);
                *balance = 0;
            }
            else if((*t)->factor == 0){
                (*t)->factor = -1;
            }
            else{
                (*t)->factor = 0;
                *balance = 0;
            }
        }
    }

    return 1;
}


int rotate_right(AVLTree **t){
    if(not t or not (*t) or not (*t)->left) return 0;
    AVLTree *aux = (*t)->left;
    (*t)->left = aux->right;
    aux->right = (*t);

    (*t)->factor = 0;
    aux->factor = 0;

    *t = aux;
    return 1;
}


int rotate_left(AVLTree **t){
    if(not t or not (*t) or not (*t)->right) return 0;
    AVLTree *aux = (*t)->right;
    (*t)->right = aux->left;
    aux->left = (*t);

    (*t)->factor = 0;
    aux->factor = 0;

    *t = aux;
    return 1;
}

int balance_left(AVLTree **t){
    if((*t)->left->factor > 0){
        return rotate_right(t);
    }
    else{
        if(rotate_left(&(*t)->left)){
            return rotate_right(t);
        }
        return 0;
    }
}


int balance_right(AVLTree **t){
    if((*t)->right->factor < 0){
        return rotate_left(t);
    }
    else{
        if(rotate_right(&(*t)->right)){
            return rotate_left(t);
        }
        return 0;
    }
}

int remove_AVL(AVLTree **t, int target, int *balance){
    if(not t or not (*t)) return 0;

    bool two = false;
    if(target == (*t)->info.data){
        
        if(not (*t)->left and not (*t)->right){
            free((*t)->info.str);
            free(*t);
            *t = NULL;
            *balance = 1;
            return 1;
        }

        else if(not (*t)->left and (*t)->right){
            AVLTree *aux;
            aux = *t;
            *t = (*t)->right;
            free(aux->info.str);
            free(aux);
            *balance = 1;
            return 1;
        }

        else if((*t)->left and not (*t)->right){
            AVLTree *aux;
            aux = *t;
            *t = (*t)->left;
            free(aux->info.str);
            free(aux);
            *balance = 1;
            return 1;
        }

        else{
            AVLTree *aux;
            aux = (*t)->left;
            while(aux->right != NULL){
                aux = aux->right;
            }

            target = (*t)->info.data;

            Info auxf = (*t)->info;
            (*t)->info = aux->info;
            aux->info = auxf;
            two = true;
        }
    }

    if(target <= (*t)->info.data or two){
        if(remove_AVL(&(*t)->left, target, balance) and *balance == 1){
            
            if((*t)->factor == 1){
                (*t)->factor = 0;
                *balance = 0;
            }
            else if((*t)->factor == 0){
                (*t)->factor = -1;
            }
            else{
                balance_right(t);
                *balance = 0;
            }
            return 1;
        }
    }

    else{
        if(remove_AVL(&(*t)->right, target, balance) and *balance == 1){

            if((*t)->factor == -1){
                (*t)->factor = 0;
                *balance = 0;
            }
            else if((*t)->factor == 0){
                (*t)->factor = 1;
            }
            else{
                balance_left(t);
                *balance = 0;
            }
            return 1;
        }
    }

    return 0;
}