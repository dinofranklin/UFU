#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H

struct student{
    int age;
    char *name;
    char *course;
};

typedef struct student Student;

typedef struct bintree BinTree;

Student make_student(int age, char *name, char *course);

BinTree *make_bintree();

int empty_bintree(BinTree *t);

int insert_bintree(BinTree **t, Student s);

int remove_bintree(BinTree **t, int target);

void free_bintree(BinTree **t);

void free_student(Student *s);

int search_bintree(BinTree *t, int target);

void show_bintree(BinTree *t);

void show_ordered(BinTree *t);

void show_treeview(BinTree *t, int space);

void print_student(Student s);

Student oldest(BinTree *t);

int plus_18(BinTree *t);

int one_son(BinTree *t);

int complete(BinTree *t, int clevel, int *plevel, int *flevel);

int height_bintree(BinTree *t);

int age_interval(BinTree *t, int begin, int end);

int nodes_bintree(BinTree *t);

void get_sorted(BinTree *t, Student *arr, int *index);

Student* merge_students(Student *arr1, Student *arr2, int size1, int size2);

BinTree *array_bintree(Student *arr, int begin, int end);

BinTree *merge_bintree(BinTree *t1, BinTree *t2);

#endif