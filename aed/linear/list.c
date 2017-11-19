#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define and &&
#define or  ||
#define not !

List *make_list(){
    List *l = (List *) malloc(sizeof(List));
    if(not l) return l;
    l->size = 0;
    l->head = NULL;
    l->last = NULL;
    return l;
}

int push(List *l, int data){
    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if(not new) return -1;    
    new->data = data;
    new->next = NULL;

    if(not l->head){
        l->head = new;
    }
    else{
        l->last->next = new;
    }
    l->last = new;

    l->size++;
    return 1;
}

int insert(List *l, int data, int pos){
    if(pos < 0 or pos > l->size) return -1;

    ListNode *new = (ListNode *) malloc(sizeof(ListNode));
    if(not new) return -1;
    new->data = data;

    int i = 0;
    ListNode *cur, *prev;
    cur = l->head;
    prev = NULL;

    while(i != pos){
        prev = cur;
        cur = cur->next;
        i++;
    }

    if(not prev){
        new->next = l->head;
        l->head = new;
        if(not l->last) l->last = new;
    }
    else{
        prev->next = new;
        new->next = cur;
        if(prev == l->last) l->last = new;
    }
    
    l->size++;
    return 1;
}

int pop(List *l){
    if(not l) return -1;
    ListNode *aux, *prev;
    prev = NULL;
    
    for(aux=l->head; aux!=l->last; aux=aux->next){
        prev = aux;
    }
    if(prev == NULL){
        l->head = NULL;
    }
    else{
        printf("DATA PREV = %d, DATA LAST = %d\n", prev->data, l->last->data);
        prev->next = NULL;
    }

    l->last = prev;
    free(aux);
    l->size--;
    return 1;
}

int list_remove(List *l, int pos){
    if(not l or pos < 0 or pos >= l->size) return -1;
    ListNode *aux, *prev;
    int i = 0;
    aux = l->head;
    prev = NULL;

    while(i != pos){
        prev = aux;
        aux = aux->next;
        i++;
    }

    if(not prev){
        l->head = aux->next;
        if(l->last == aux) l->last = NULL;
    }
    else{
        prev->next = aux->next;
        if(l->last == aux) l->last = prev;
    }
    
    l->size--;
    free(aux);
    return 0;
}

void print_list(List *l){
    if(not l or not l->size){
        printf("Empty list!\n");
        return;
    }

    ListNode *aux;
    printf("List: [ ");
    for(aux=l->head; aux!=NULL; aux=aux->next){
        printf("%d", aux->data);
        aux->next == NULL ? (printf(" ")) : (printf(", "));
    }
    printf("]\n");

    return;
}

int empty_list(List *l){
    if(not l or not l->size) return 1;
    else return 0;
}

int list_element(List *l, int pos){
    if(not l or pos < 0 or pos >= l->size){
        printf("ERROR: INVALID LIST OR POSITION");
        return 0;
    }

    ListNode *aux = l->head;
    int i;
    for(i=0; i<l->size; ++i){
        if(i == pos){
            return aux->data;
        }
        aux = aux->next;
    }
}

void free_list(List **l){
    if(not (*l)) return;
    ListNode *aux, *next;
    
    for(aux=(*l)->head; aux!=NULL; aux=next){
        next = aux->next;
        free(aux);
    }

    free(*l);
    *l = NULL;
    return;
}