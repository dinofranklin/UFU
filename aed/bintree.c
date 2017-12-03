#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bintree.h"

#define and &&
#define not !
#define or ||


struct bintree{
    Student s;
    struct bintree *left;
    struct bintree *right;
};


//MAKES A STUDENT.
Student make_student(int age, char *name, char *course){
    Student s;
    s.age = age;
    s.name = (char *) malloc(sizeof(char)*strlen(name));
    if(not s.name){
        printf("ERROR: No memory available!\n");
    }
    strcpy(s.name, name);
    s.course = (char *) malloc(sizeof(char)*strlen(course));
    if(not s.name){
        printf("ERROR: No memory available!\n");
    }
    strcpy(s.course, course);
    return s;
}



//MAKES A BINARY SEARCH TREE.
BinTree *make_bintree(){
    return NULL;
}



//RETURNS IF A TREE IS EMPTY.
int empty_bintree(BinTree *t){
    if(not t) return 1;
    else return 0;
}



//INSERTS A STUDENT ON A TREE.
int insert_bintree(BinTree **t, Student s){
    if(not t) return 0;

    if(not (*t)){
        BinTree *new = (BinTree *) malloc(sizeof(BinTree));
        if(not new) return 0;
        new->left = NULL;
        new->right = NULL;
        new->s = s;

        *t = new;
        return 1;
    }

    else if(s.age <= (*t)->s.age){
        return insert_bintree(&(*t)->left, s);
    }
    else{
        return insert_bintree(&(*t)->right, s);
    }
}



//REMOVES A STUDENT WITH CERTAIN AGE FROM THE TREE.
int remove_bintree(BinTree **t, int target){
    if(not t or not (*t)) return 0;

    if(target == (*t)->s.age){

        if(not (*t)->left and not (*t)->right){
            free_bintree(t);
        }

        else if(not (*t)->left){
            BinTree *aux = *t;
            *t = (*t)->right;
            free(aux);
        }

        else if(not (*t)->right){
            BinTree *aux = *t;
            *t = (*t)->left;
            free(aux);
        }
        
        else{
            BinTree *temp, *aux = (*t)->left;
            temp = NULL;
            while(aux->right != NULL){
                temp = aux;
                aux = aux->right;
            }

            free_student(&(*t)->s);
            (*t)->s.age = aux->s.age;
            (*t)->s.name = aux->s.name;
            (*t)->s.course = aux->s.course;

            if(temp){
                temp->right = aux->left;
            }
            free(aux);
        }
        return 1;
    }

    else if(target <= (*t)->s.age){
        return remove_bintree(&(*t)->left, target);
    } 
    else{
        return remove_bintree(&(*t)->right, target);
    }
}



//FREES A BINARY TREE.
void free_bintree(BinTree **t){
    if(not t or not (*t)) return;
    
    free_bintree(&(*t)->left);
    free_bintree(&(*t)->right);
    free_student(&(*t)->s);
    free(*t);
    *t = NULL;
    return;
}



//FREES A STUDENT.
void free_student(Student *s){
    free(s->name);
    free(s->course);
    return;
}


//SEARCHES A STUDENTE WITH THE TARGET AGE.
int search_bintree(BinTree *t, int target){
    if(not t) return 0;
    if(target == t->s.age) return 1;
    if(target <= t->s.age) return search_bintree(t->left, target);
    return search_bintree(t->right, target);
}



//PRINTS THE BINARY TREE.
void show_bintree(BinTree *t){
    if(not t){
        printf("<>");
        return;
    }
    
    printf("<%d", t->s.age);
    show_bintree(t->left);
    show_bintree(t->right);
    printf(">");
    return;
}



//PRINTS THE BINARY TREE IN ORDER.
void show_ordered(BinTree *t){
    if(not t) return;

    show_ordered(t->left);
    printf("%d ", t->s.age);
    show_ordered(t->right);

    return;
}



//PRINTS THE BINARY TREE IN TREEVIEW. THE BEST!!!
void show_treeview(BinTree *t, int space){
    if(not t) return;

    int i;
    for(i=0; i<space; ++i){
        putchar(' ');
    }
    putchar('|');
    print_student(t->s);

    show_treeview(t->left, space+5);
    show_treeview(t->right, space+5);
    return;
}



//PRINTS A STUDENT.
void print_student(Student s){
    printf("%s - %d, studies %s\n", s.name, s.age, s.course);
    return;
}



//FINDS THE OLDEST STUDENT.
Student oldest(BinTree *t){
    if(not t){
        Student s;
        s.age = -1;
        s.name = NULL;
        s.course = NULL;
        return s;
    }

    BinTree *aux = t;
    while(aux->right != NULL){
        aux = aux->right;
    }
    return aux->s;
}



//COUNTS THE STUDENTS WITH 18+ YEARS OLD. 
int plus_18(BinTree *t){
    if(not t) return 0;

    if(t->s.age >= 18){
        return 1+plus_18(t->left)+plus_18(t->right);
    }
    else return plus_18(t->right);
}



//COUNTS THE NODES WITH ONE SON.
int one_son(BinTree *t){
    if(not t) return 0;

    if(not t->left and t->right){
        return 1+one_son(t->right);
    }
    if(t->left and not t->right){
        return 1+one_son(t->left);
    }
    if(t->left and t->right){
        return one_son(t->right)+one_son(t->left);
    }
    return 0;
}



//CHECKS IF A TREE IS COMPLETE. Curent, Final - 1, Final.
int complete(BinTree *t, int clevel, int *plevel, int *flevel){
    if(not t) return 1;

    if((t->left and not t->right) or (not t->left and t->right)) return 0;

    if(not t->left and not t->right){
        if(*plevel == -1){
            *plevel = clevel;
            return 1;
        }
        else if(clevel == *plevel or clevel == *flevel){
            return 1;
        }
        else if(*flevel == -1){
            if(clevel+1 == *plevel or clevel-1 == *plevel){
                *flevel = clevel;
                return 1;
            }
            return 0;
        }
    }

    else{
        if(complete(t->left, clevel+1, plevel, flevel)){
            return complete(t->right, clevel+1, plevel, flevel);
        }
        return 0;
    }
}



//RETURNS THE HEIGHT OF THE TREE.
int height_bintree(BinTree *t){
    if(not t) return -1;

    int hl, hr;
    hl = height_bintree(t->left);
    hr = height_bintree(t->right);

    return 1+ (hl>hr ? hl : hr);
}



//COUNTS THE STUDENTS BETWEEN AN AGE INTERVAL.
int age_interval(BinTree *t, int begin, int end){
    if(not t) return 0;

    if(t->s.age < begin) return age_interval(t->right, begin, end);
    if(t->s.age > end) return age_interval(t->left, begin, end);
    else return 1+age_interval(t->right, begin, end)+age_interval(t->left, begin, end);
}



//COUNTS THE NODES OF A TREE.
int nodes_bintree(BinTree *t){
    if(not t) return 0;
    return 1+nodes_bintree(t->left)+nodes_bintree(t->right);
}



//GET A SORTED ARRAY FROM A BINARY TREE.
void get_sorted(BinTree *t, Student *arr, int *index){
    if(not t) return;

    get_sorted(t->left, arr, index);
    arr[*index] = t->s;
    (*index)++;
    get_sorted(t->right, arr, index);
    return;
}



//MERGES TWO ARRAYS OF STUDENTS.
Student* merge_students(Student *arr1, Student *arr2, int size1, int size2){
    int i, j, k;
    Student *merged = (Student *) malloc(sizeof(Student)*(size1+size2));
    i = j = k = 0;

    while(i<size1 and j<size2){
        if(arr1[i].age < arr2[j].age){
            merged[k++] = arr1[i++];
        }
        else{
            merged[k++] = arr2[j++];
        }
    }

    while(i<size1){
        merged[k++] = arr1[i++];
    }
    while(j<size2){
        merged[k++] = arr2[j++];
    }

    return merged;
}



//TRANSFORMS AN ARRAY IN A BINARY TREE.
BinTree *array_bintree(Student *arr, int begin, int end){
    if(begin > end) return NULL;

    int mid = (begin+end)/2;
    BinTree *new = (BinTree *) malloc(sizeof(BinTree));
    new->s = arr[mid];
    
    new->left = array_bintree(arr, begin, mid-1);
    new->right = array_bintree(arr, mid+1, end);

    return new;
}



//MERGES TWO TREES.
BinTree *merge_bintree(BinTree *t1, BinTree *t2){
    int n1, n2, index;
    Student *arr1, *arr2, *merged;
    
    n1 = nodes_bintree(t1);
    n2 = nodes_bintree(t2);

    arr1 = (Student *) malloc(sizeof(Student)*n1);
    arr2 = (Student *) malloc(sizeof(Student)*n2);

    index = 0;
    get_sorted(t1, arr1, &index);
    index = 0;
    get_sorted(t2, arr2, &index);

    merged = merge_students(arr1, arr2, n1, n2);
    BinTree *final = array_bintree(merged, 0, n1+n2-1);

    free(arr1);
    free(arr2);
    free(merged);

    return final;
}