#ifndef AVL_TREE
#define AVL_TREE

struct info{
    int data;
    char *str;
};

typedef struct info Info;

typedef struct avltree AVLTree;

Info make_register(int value, char *str);

AVLTree *make_avl();

int empty_AVL(AVLTree *t);

int search_avl(AVLTree *t, int target);

void show_avl(AVLTree *t);

void free_avl(AVLTree **t);

void ordered_avl(AVLTree *t);

int insert_AVL(AVLTree **t, Info f, int *balance);

int rotate_right(AVLTree **t);

int rotate_left(AVLTree **t);

int balance_left(AVLTree **t);

int balance_right(AVLTree **t);

int remove_AVL(AVLTree **t, int target, int *balance);

void treeview_avl(AVLTree *t, int space);

#endif
