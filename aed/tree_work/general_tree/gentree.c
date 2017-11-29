#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gentree.h"

#define QUEUEMAX 1000
#define and &&
#define not !
#define or ||



//STRUCT OF A GENERIC TREE.
struct gentree{
    int data;
    struct gentree *son;
    struct gentree *brother;
};



//MAKES A GENERIC TREE WITH VALUE AS DATA.
GenTree *make_gentree(int value){
    GenTree *new = (GenTree *) malloc (sizeof(GenTree));
    if(not new) return new;
    
    new->data = value;
    new->son = NULL;
    new->brother = NULL;
    
    return new;
}



//INSERTS A GENERIC TREE S AS THE SON OF A TREE T.
int insertson_gentree(GenTree *t, GenTree *s){
    if(not t or not s) return -1;
    if(s->brother) return 0;

    s->brother = t->son;
    t->son = s;
    return 1;
}



//INSERTS A GENERIC TREE S AS THE FATHER OF A TREE T.
int insertfather_gentree(GenTree **t, GenTree *s){
    if(not (*t) or not t or not s) return -1;
    if(s->brother) return 0;
   
    s->son = *t;
    *t = s;
    return 1;
}



//INSERTS A TREE S AS SON OF A TREE T WITH ROOT DATA = VALUE.
int insertnode_gentree(GenTree *t, GenTree *s, int value){
    if(not t or not s) return -1;
    if(s->brother) return 0;

    if(t->data == value){
        s->brother = t->son;
        t->son = s;
        return 1;
    }

    if(insertnode_gentree(t->son, s, value) == 1) return 1;
    else if(insertnode_gentree(t->brother, s, value) == 1) return 1;
    return 0;
}



//REMOVES A VALUE FROM A GENERIC TREE.
int remove_gentree(GenTree **t, int value){
    if(not t or not (*t)) return 0;

    if((*t)->data == value){
        GenTree *aux = *t;
        free_gentree(&(*t)->son);
        *t = (*t)->brother;
        free(aux);
        return 1;   
    }

    else if(remove_gentree(&(*t)->son, value) == 1) return 1;
    else if(remove_gentree(&(*t)->brother, value) == 1) return 1;
    return 0;
}



//SHOW A GENERIC TREE.
void show_gentree(GenTree *t){
    if(not t){
        printf("<>");
        return;
    }

    printf("<%d", t->data);
    show_gentree(t->son);
    printf(">");
    show_gentree(t->brother);
    return;
}



//SEARCHES A GENERIC TREE FOR AN ELEMENT.
int search_gentree(GenTree *t, int target){
    if(not t) return 0;
    
    if(t->data == target) return 1;

    if(search_gentree(t->son, target)) return 1;
    if(search_gentree(t->brother, target)) return 1;
    return 0;
}



//FREE A GENERIC TREE.
void free_gentree(GenTree **t){
    if(not t or not (*t)) return;

    free_gentree(&(*t)->son);
    free_gentree(&(*t)->brother);

    free(*t);
    *t = NULL;
    return;
}



//FINDS THE HEIGHT OF A GENERIC TREE.
int height_gentree(GenTree *t){
    if(not t) return -1;

    int hs, hb;
    hs = 1 + height_gentree(t->son);
    hb = height_gentree(t->brother);

    if(hs>hb) return hs;
    return hb;
}



//TRAVERSE A TREE IN PREORDER.
void pre_order(GenTree *t){
    if(not t) return;

    printf("%d ", t->data);
    pre_order(t->son);
    pre_order(t->brother);

    return;
}



//TRAVERSE A TREE IN POSTORDER.
void post_order(GenTree *t){
    if(not t) return;

    post_order(t->son);
    printf("%d ", t->data);
    post_order(t->brother);

    return;
}



//TRAVERSE A TREE BY LEVEL.
void traverse_level(GenTree *t){
    if(not t) return;

    int i, j;
    GenTree *aux, *cur;
    GenTree **vet = (GenTree **) malloc(QUEUEMAX*sizeof(GenTree *));
    
    printf("good on alocation!\n");
    i = j = 0;
    vet[j++] = t;
    vet[j++] = t->son;
    printf("good on assing\n");

    while(j <= j){
        cur = vet[i++];
        if(cur == NULL) break;
        printf("%d ", cur->data);

        for(aux=cur->brother; aux!=NULL; aux=aux->brother){
            if(aux->son) vet[j++] = aux->son;
            printf("%d ", aux->data);
        }
    }
    
    return;
}



//RETURNS THE NUMBER OF LEAF NODES A GENERIC TREE HAS.
int leafs(GenTree *t){
    if(not t) return 0;
    if(not t->son) return 1 + leafs(t->brother);

    return leafs(t->son) + leafs(t->brother);
}



//RETURNS THE DEGREE OF A GENERAL TREE.
int gentree_degree(GenTree *t){
    if(not t) return -1;

    int degree = 0;
    GenTree *aux;
    for(aux=t->son; aux != NULL; aux=aux->brother){
        ++degree;
    }
    return degree;
}



//FINDS THE NUMBER OF NODES OF A TREE WITH GIVEN DEGREE.
int nodes(GenTree *t, int degree){
    if(not t) return -1;

    if(gentree_degree(t) == degree){
        return count_nodes(t->son);
    }

    int r;
    r = nodes(t->son, degree);
    if(r != -1) return r;
    return nodes(t->brother, degree);
}



//COUNTS THE NUMBER OF NODES IN A TREE.
int count_nodes(GenTree *t){
    if(not t) return 0;
    return 1+count_nodes(t->brother)+count_nodes(t->son);
}



//FINDS THE HEIGHT OF A GIVEN NODE IN A GENERIC TREE.
int node_height(GenTree *t, int value){
    if(not t) return -1;
    
    int hei;
    if(t->data == value){
        GenTree *aux = (GenTree *) malloc(sizeof(GenTree));
        aux->data = value;
        aux->son = t->son;
        aux->brother = NULL;

        hei = height_gentree(aux);
        free(aux);
        return hei;
    }

    hei = node_height(t->son, value);
    if(hei != -1) return hei;
    return node_height(t->brother, value);
}



//PRINTS A TREE VIEW.
void print_treeview(GenTree *t, int spc){
    int i;
    if(not t) return;

    for(i=0; i<spc; ++i){
        putchar(' ');
    }
    printf("|%d\n", t->data);
    print_treeview(t->son, spc+3);
    print_treeview(t->brother, spc);
    return;
}