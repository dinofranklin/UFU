#ifndef LIST_H
#define LIST_H

#define LSIZE 26

typedef struct city{
    char name;
    struct city *next;
}City;

typedef struct list{
    char main;
    int size;
    struct city *head;
    struct city *tail;
}List;

List **make_lists();

void add_city(List *l, char name);

void remove_city(List *l);

int list_size(List *l);

char list_position(List *l, int pos);

void destroy_lists(List **l);

void show_lists(List **l);

#endif
