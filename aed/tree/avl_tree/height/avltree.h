#ifndef AVLTREE
#define AVLTREE

typedef struct avl Avl;

Avl *make_avl();

int empty_avl(Avl *t);

int search_avl(Avl *t, int target);

void show_avl(Avl *t);

void free_avl(Avl **t);

void ordered_avl(Avl *t);

int rotate_right(Avl **t);

int rotate_left(Avl **t);

int balance_right(Avl **t);

int balance_left(Avl **t);

int insert_avl(Avl **t, int value);

int remove_avl(Avl **t, int target);

void treeview_avl(Avl *t, int space);

#endif
