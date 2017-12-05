#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"

#define and &&
#define not !
#define or ||


struct avltree{
    int height;
    NetNode node;
    struct avltree *left;
    struct avltree *right;
};



//MAKES A NODE
NetNode make_node(int id, int traffic, int capacity, char *location){
    NetNode n;
    n.id = id;
    n.traffic = traffic;
    n.capacity = capacity;
    n.location = (char *) malloc(strlen(location)*sizeof(char));
    if(not n.location){
        printf("ERROR: No memory available!\n");
        return n;
    }
    strcpy(n.location, location);
    return n;
}



//MAKES AN AVLTREE.
AvlTree *make_avltree(){
    return NULL;
}



//CHECKS IF A TREE IS EMPTY.
int empty_avltree(AvlTree *t){
    if(not t) return 1;
    else return 0;
}



//SEARCHES FOR AN ELEMENT.
int search_avltree(AvlTree *t, int target){
    if(not t) return 0;

    if(target == t->node.traffic) return 1;
    if(target <= t->node.traffic) return search_avltree(t->left, target);
    return search_avltree(t->right, target);
}



//SHOW AN AVL TREE - NOTATION.
void show_avl(AvlTree *t){
    if(not t){
        printf("<>");
        return;
    }

    printf("<%d", t->node.traffic);
    show_avl(t->left);
    show_avl(t->right);
    printf(">");
    return;
}



//SHOW AN AVL TREE - ORDERED.
void ordered_avl(AvlTree *t){
    if(not t) return;

    ordered_avl(t->left);
    printf("%d ", t->node.traffic);
    ordered_avl(t->right);

    return;
}



//SHOW AN AVL TREE - TREEVIEW.
void treeview_avl(AvlTree *t, int space){
    if(not t) return;

    int i;
    for(i=0; i<space; ++i){
        putchar(' ');
    }
    
    putchar('|');
    print_node(t->node);

    treeview_avl(t->left, space+5);
    treeview_avl(t->right, space+5);
    return;
}



//PRINTS A NODE INFORMATION.
void print_node(NetNode n){
    printf("id: %d at %s, %d of %d.\n", n.id, n.location, n.traffic, n.capacity);
    return;
}



//FREES AN AVL TREE.
void free_avl(AvlTree **t){
    if(not t or not (*t)) return;

    free_avl(&(*t)->left);
    free_avl(&(*t)->right);
    free((*t)->node.location);
    free(*t);
    *t = NULL;

    return;
}




//ROTATES RIGHT.
int rotate_right(AvlTree **t){
    if(not t or not (*t) or not (*t)->left) return 0;

    AvlTree *aux = (*t)->left;
    int tl, sl;

    tl = (*t)->right == NULL ? -1 : (*t)->right->height;
    sl = aux->right == NULL ? -1 : aux->right->height;
    (*t)->height = 1 + (tl > sl ? tl : sl);
    aux->height = 1 + (*t)->height;
    
    (*t)->left = aux->right;
    aux->right = (*t);

    *t = aux;
    return 1;
}



//ROTATES LEFT.
int rotate_left(AvlTree **t){
    if(not t or not (*t) or not (*t)->right) return 0;

    AvlTree *aux = (*t)->right;
    int tl, sl;

    tl = (*t)->left == NULL ? -1 : (*t)->left->height;
    sl = aux->left == NULL ? -1 : aux->left->height;
    (*t)->height = 1 + (tl > sl ? tl : sl);
    aux->height = (*t)->height + 1;    

    (*t)->right = aux->left;
    aux->left = (*t);

    *t = aux;
    return 1;
}



//BALANCES THE TREE.
int balance_right(AvlTree **t){
    if(not t or not (*t) or not (*t)->right) return 0;

    AvlTree *son = (*t)->right;
    int hl, hr;
    hl = son->left == NULL ? -1 : son->left->height;
    hr = son->right == NULL ? -1 : son->right->height;

    if(hl-hr <= 0){
        return rotate_left(t);
    }
    else{
        if(rotate_right(&(*t)->right)){
            return rotate_left(t);
        }
        return 0;
    }
}



//BALANCES THE TREE.
int balance_left(AvlTree **t){
    if(not t or not (*t) or not (*t)->left) return 0;

    AvlTree *son = (*t)->left;
    int hl, hr;
    hl = son->left == NULL ? -1 : son->left->height;
    hr = son->right == NULL ? -1 : son->right->height;

    if(hl-hr >= 0){
        return rotate_right(t);
    }
    else{
        if(rotate_left(&(*t)->left)){
            return rotate_right(t);
        }
        return 0;
    }
}



//INSERTS A NODE IN AN AVLTREE.
int insert_avl(AvlTree **t, NetNode n){
    if(not t) return 0;

    if(not (*t)){
        AvlTree *new = (AvlTree *) malloc(sizeof(AvlTree));
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        new->node = n;
        *t = new;
    }

    else if(n.traffic <= (*t)->node.traffic){
        if(not insert_avl(&(*t)->left, n)) return 0;

        if((*t)->height == (*t)->left->height){
            (*t)->height++;
        }

        int rh = (*t)->right == NULL ? -1 : (*t)->right->height;
        if((*t)->left->height - rh > 1){
            return balance_left(t);
        }
    }

    else{
        if(not insert_avl(&(*t)->right, n)) return 0;

        if((*t)->height == (*t)->right->height){
            (*t)->height++;
        }

        int lh = (*t)->left == NULL ? -1 : (*t)->left->height;
        if(lh - (*t)->right->height < -1){
            return balance_right(t);
        }
    }

    return 1;
}



//REMOVES A NODE FROM THE TREE.
int remove_avl(AvlTree **t, int target){
    if(not t or not (*t)) return 0;

    if(target == (*t)->node.traffic){

        if(not (*t)->left and not (*t)->right){
            free((*t)->node.location);
            free(*t);
            *t = NULL;
        }

        else if(not (*t)->left){
            AvlTree *aux = *t;
            *t = (*t)->right;
            free(aux->node.location);
            free(aux);
        }

        else if(not (*t)->right){
            AvlTree *aux = *t;
            *t = (*t)->left;
            free(aux->node.location);
            free(aux);
        }

        else{
            AvlTree *aux;
            AvlTree **addrs = &(*t)->left;

            aux = (*t)->left;
            while(aux->right){
                aux = aux->right;
            }

            free((*t)->node.location);
            (*t)->node = aux->node;

            *addrs = aux->left;
        }
        return 1;
    }

    else if(target <= (*t)->node.traffic){
        if(not remove_avl(&(*t)->left, target)) return 0;

        int hl, hr;
        
        hl = (*t)->left == NULL ? -1 : (*t)->left->height;
        hr = (*t)->right == NULL ? -1 : (*t)->right->height;

        (*t)->height = 1 + (hl > hr ? hl : hr);

        if(hl-hr < -1) return balance_right(t);
    }

    else{
        if(not remove_avl(&(*t)->right, target)) return 0;

        int hl, hr;

        hl = (*t)->left == NULL ? -1 : (*t)->left->height;
        hr = (*t)->right == NULL ? -1 : (*t)->right->height;

        (*t)->height = 1 + (hl > hr ? hl : hr);

        if(hl-hr > 1) return balance_left(t);
    }
    return 1;
}



//FINDS THE NODE WITH LEAST TRAFFIC.
NetNode least_traffic(AvlTree *t){
    AvlTree *aux = t;
    while(aux->left) aux = aux->left;

    return aux->node;
}



//COUNTS THE IDLE NODES.
int count_idle(AvlTree *t){
    if(not t) return 0;

    if(t->node.traffic < t->node.capacity/2){
        return 1+count_idle(t->left)+count_idle(t->right);
    }
    return count_idle(t->left)+count_idle(t->right);
}



//COUNTS THE INTERNAL NODES.
int count_internal(AvlTree *t){
    if(not t) return 0;
    if(not t->left and not t->right) return 0;

    return 1+count_internal(t->left)+count_internal(t->right);
} 



//CHECKS IF THE TREE IS FULL.
int check_full(AvlTree *t, int level){
    if(not t) return 0;

    int lvl, lvr;
    lvl = check_full(t->left, level+1);
    lvr = check_full(t->right, level+1);

    if(lvl == lvr) return 1;
    else return 0;
}



//CHECKS IF THE TREE IS FULL - AUXILIARY.
int full(AvlTree *t){
    if(not t) return 0;
    return check_full(t, 0);
}



//FINDS THE LEVEL OF A NODE.
int find_level(AvlTree *t, NetNode n, int level){
    if(not t) return -1;

    if(compare_nodes(t->node, n)) return level;
    
    if(n.traffic <= t->node.traffic){
        return find_level(t->left, n, level+1);
    }

    return find_level(t->right,n,level+1);
}



//FINDS THE LEVEL OF A NODE - AUXILIARY.
int level_of(AvlTree *t, NetNode n){
    if(not t) return -1;
    else return find_level(t, n, 0);
}



//FINDS IF TWO TREES ARE EQUAL.
int equal_avl(AvlTree *t1, AvlTree *t2){
    if(not t1 and not t2) return 1;
    if(not t1 and t2) return 0;
    if(t1 and not t2) return 0;

    if(not equal_avl(t1->left, t2->left)) return 0;
    if(not equal_avl(t1->right, t2->right)) return 0;

    return compare_nodes(t1->node, t2->node);
}



int compare_nodes(NetNode n1, NetNode n2){
    if(n1.capacity != n2.capacity) return 0;
    if(n1.traffic != n2.traffic) return 0;
    if(n1.id != n2.id) return 0;
    if(strcmp(n1.location, n2.location)) return 0;
    return 1; 
}