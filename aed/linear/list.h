#ifndef LIST_H
#define LIST_H

struct listnode{
    int data;
    struct listnode *next;
};

struct list{
    int size;
    struct listnode *head;
    struct listnode *last;
};

typedef struct listnode ListNode;
typedef struct list List;

List *make_list();

int push(List *l, int data);

int insert(List *l, int data, int pos);

int pop(List *l);

int list_remove(List *l, int pos);

void print_list(List *l);

int empty_list(List *l);

int list_element(List *l, int pos);

void free_list(List **l);

#endif