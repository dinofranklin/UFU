#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List **make_lists(){
    int i;
    List **l = (List **) malloc(LSIZE*sizeof(List *));
    for(i = 0; i < LSIZE; ++i){
        l[i] = (List *) malloc(sizeof(List));
        l[i]->main = 'A'+i;
        l[i]->size = 0;
        l[i]->head = NULL;
        l[i]->tail = NULL;
    }
    return l;
}

void add_city(List *l, char name){
    City *new = (City *) malloc(sizeof(City));
    new->next = NULL;
    new->name = name;
    if(!l->size){
        l->head = new;
    }
    else{
        l->tail->next = new;
    }
    l->tail = new;
    ++(l->size);
    return;
}

void remove_city(List *l){
    City *aux = l->head;
    if(aux->next == NULL){
        l->tail = NULL;
    }
    l->head = l->head->next;
    free(aux);
    --(l->size);
    return;
}

int list_size(List *l){
    return l->size;
}

char list_position(List *l, int pos){
    City *aux = l->head;
    while(1){
        if(pos == 1) return aux->name;
        aux = aux->next;
        --pos;
    }
}

void destroy_lists(List **l){
    int i;
    for(i = 0; i < LSIZE; ++i){
        while(list_size(l[i])){
            remove_city(l[i]);
        }
        free(l[i]);
    }
    free(l);
    return;
}

void show_lists(List **l){
    int i;
    for(i = 0; i < LSIZE; ++i){
        printf("List %c: [ ", l[i]->main);
        City *aux = l[i]->head;
        while(aux != NULL){
            printf("%c ", aux->name);
            aux = aux->next;
        }
        printf("]\n");
    }
    return;
}
