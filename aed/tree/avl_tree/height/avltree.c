#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

#define and &&
#define not !
#define or ||

struct avl{
    int height;
    int data;
    struct avl *left;
    struct avl *right;
};



Avl *make_avl(){
    return NULL;
}



int empty_avl(Avl *t){
    if(not t) return 1;
    return 0;
}



int search_avl(Avl *t, int target){
    if(not t) return 0;

    if(target == t->data) return 1;
    if(target >= t->data) return search_avl(t->left, target);
    return search_avl(t->right, target);
}



void show_avl(Avl *t){
    if(not t){
        printf("<>");
        return;
    }

    printf("<%d", t->data);
    show_avl(t->left);
    show_avl(t->right);
    printf(">");
    return;
}



void free_avl(Avl **t){
    free_avl(&(*t)->left);
    free_avl(&(*t)->right);
    free(*t);
    *t = NULL;
    return;
}



void ordered_avl(Avl *t){
    if(not t) return;

    ordered_avl(t->left);
    printf("%d ", t->data);
    ordered_avl(t->right);

    return;
}



int rotate_right(Avl **t){
    if(not t or not (*t) or not (*t)->left) return 0;

    Avl *aux = (*t)->left;
    (*t)->height = aux->left == NULL ? 0 : aux->left->height;
    aux->height = (*t)->height + 1;

    (*t)->left = aux->right;
    aux->right = (*t);

    *t = aux;
    return 1;
}



int rotate_left(Avl **t){
    if(not t or not (*t) or not (*t)->right) return 0;

    Avl *aux = (*t)->right;
    (*t)->height = aux->right == NULL ? 0 : aux->right->height;
    aux->height = (*t)->height + 1;

    (*t)->right = aux->left;
    aux->left = (*t);

    *t = aux;
    return 1;
}



int balance_right(Avl **t){
    if(not t or not (*t) or not (*t)->right) return 0;

    Avl *son = (*t)->right;
    int rhei, lhei;
    lhei = son->left == NULL ? -1 : son->left->height;
    rhei = son->right == NULL ? -1 : son->right->height;
    
    if(lhei - rhei < 0){
        return rotate_left(t);
    }
    else{
        if(rotate_right(&(*t)->right)){
            return rotate_left(t);
        }
        return 0;
    }
}



int balance_left(Avl **t){
    if(not t or not (*t) or not (*t)->left) return 0;

    Avl *son = (*t)->left;
    int rhei, lhei;
    lhei = son->left == NULL ? -1 : son->left->height;
    rhei = son->right == NULL ? -1 : son->right->height;
    
    if(lhei - rhei > 0){
        return rotate_right(t);
    }
    else{
        if(rotate_left(&(*t)->left)){
            return rotate_right(t);
        }
        return 0;
    }
}



int insert_avl(Avl **t, int value){
    if(not t) return 0;

    //VAZIA.
    if(not (*t)){
        Avl *new = (Avl *) malloc(sizeof(Avl));
        new->left = NULL;
        new->right = NULL;
        new->data = value;
        new->height = 0;

        *t = new;
    }

    //EH MENOR.
    else if(value <= (*t)->data){
        insert_avl(&(*t)->left, value);

        if((*t)->left->height == (*t)->height){
            (*t)->height++;
        }

        int rhei = (*t)->right == NULL ? -1 : (*t)->right->height;
        if((*t)->left->height - rhei == 2){
            balance_left(t);
        }
    }

    else{
        insert_avl(&(*t)->right, value);
        
        if((*t)->right->height == (*t)->height){
            (*t)->height++;
        }

        int lhei = (*t)->left == NULL ? -1 : (*t)->left->height;
        if(lhei - (*t)->right->height == -2){
            balance_right(t);
        }
    }
    return 1;
}


int remove_avl(Avl **t, int target){
    if(not t or not (*t)) return 0;

    //ACHEI 
    if(target == (*t)->data){

        if((*t)->left == NULL and (*t)->right == NULL){
            free(*t);
            *t = NULL;
            return 1;
        }

        else if((*t)->left == NULL){
            Avl *aux = *t;
            *t = (*t)->right;
            free(aux);
            return 1;
        }

        else if((*t)->right == NULL){
            Avl *aux = *t;
            *t = (*t)->left;
            free(aux);
            return 1;
        }

        else{
            int auxval;
            Avl *aux = (*t)->left; 
            while(aux->right != NULL){
                aux = aux->right;
            }

            target = aux->data;
            (*t)->data = aux->data;
        }
    }

    if(target <= (*t)->data){
        if(remove_avl(&(*t)->left, target)){
            int rh, lh;
            rh = (*t)->right == NULL ? -1 : (*t)->right->height;
            lh = (*t)->left == NULL ? -1 : (*t)->left->height;
            
            (*t)->height = 1 + (rh > lh ? rh : lh);
            if(lh - rh < -1){
                balance_right(t);
            }
        }
    }

    else{
        if(remove_avl(&(*t)->right, target)){
            int rh, lh;
            rh = (*t)->right == NULL ? -1 : (*t)->right->height;
            lh = (*t)->left == NULL ? -1 : (*t)->left->height;

            (*t)->height = 1 + (rh > lh ? rh : lh);
            if(lh - rh > 2){
                balance_right(t);
            }
        }
    }
    return 1;
}



void treeview_avl(Avl *t, int space){
    if(not t) return;

    int i;
    for(i=0; i<space; ++i){
        putchar(' ');
    }

    printf("|%d - %d\n", t->data, t->height);
    treeview_avl(t->left, space+5);
    treeview_avl(t->right, space+5);
    return;
}
