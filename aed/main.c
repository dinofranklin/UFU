#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "bintree.h"

#if defined(_WIN32) || defined(_WIN64)
    const char* CLEAR = "cls";
#else
#ifdef __linux
    const char* CLEAR = "clear";
#endif
#endif

#define and &&
#define not !
#define or ||
#define MAXTREE 10
#define MAXBUFFER 1000

char buffer[MAXBUFFER];

//FUNCTION DECLARATIONS.
int menu();
int get_int(int *ans);
int write_and_scan(char *msg, int *ans);
int get_string(char *str, int size);
int wanted_tree(int *size);

//AUXILIARY FUNCTIONS.
void insert_aux(BinTree **trees, int *size);
void empty_aux(BinTree **trees, int *size);
void make_aux(BinTree **trees, int *size);
void remove_aux(BinTree **trees, int *size);
void search_aux(BinTree **trees, int *size);
void show_aux(BinTree **trees, int *size);
void ordered_aux(BinTree **trees, int *size);
void treeview_aux(BinTree **trees, int *size);
void oldest_aux(BinTree **trees, int *size);
void plus18_aux(BinTree **trees, int *size);
void interval_aux(BinTree **trees, int *size);
void oneson_aux(BinTree **trees, int *size);
void complete_aux(BinTree **trees, int *size);
void merge_aux(BinTree **trees, int *size);
void height_aux(BinTree **trees, int *size);
void free_aux(BinTree **trees, int *size);


int main(){
    int op, size = 0;
    BinTree **trees = (BinTree **) malloc(MAXTREE*sizeof(BinTree *));

    while(true){
        op = menu();
        if(op == 1) make_aux(trees, &size);
        else if(op ==  2) empty_aux(trees, &size);
        else if(op ==  3) insert_aux(trees, &size);
        else if(op ==  4) remove_aux(trees, &size);
        else if(op ==  5) search_aux(trees, &size);
        else if(op ==  6) show_aux(trees, &size);
        else if(op ==  7) ordered_aux(trees, &size);
        else if(op ==  8) treeview_aux(trees, &size);
        else if(op ==  9) oldest_aux(trees, &size);
        else if(op == 10) plus18_aux(trees, &size);
        else if(op == 11) interval_aux(trees, &size);
        else if(op == 12) oneson_aux(trees, &size);
        else if(op == 13) complete_aux(trees, &size);
        else if(op == 14) height_aux(trees, &size);
        else if(op == 15) merge_aux(trees, &size);
        else if(op == 16) free_aux(trees, &size);
        else if(op == 17) break; 
        else printf("ERROR: Something went terribly wrong!\n");

        printf("Press ENTER to go back to the menu!\n");
        fgets(buffer, MAXBUFFER, stdin);
    }

    printf("Goodbye...\n");
    return 0;
}



//WRITES A STRING AND SCAN AN INTEGER.
int write_and_scan(char *msg, int *ans){
    int value;
    printf("%s", msg);
    fgets(buffer, MAXBUFFER, stdin);
    
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return 0;
    }

    *ans = value;
    return 1;
}



//AUXILIARY TO MAKE_BINTREE
void make_aux(BinTree **trees, int *size){
    if(*size == MAXTREE){
        printf("Sorry! You cant have more than %d trees!\n", *size);
        return;
    }
    trees[*size] = make_bintree();
    ++(*size);
    printf("Tree number %d was created!\n", *size);
}



//AUXILIARY TO EMPTY_TREE
void empty_aux(BinTree **trees, int *size){
    if(*size == 0){
        printf("You don't any trees, try to create some!\n");
        return;
    }

    int tr;
    if(*size == 1) tr = 1;
    else if(not write_and_scan("Type the number of the wanted tree: ", &tr)) return;
    tr--;

    if(tr < 0 or tr >= *size){
        printf("Tree not found - type a valid number (1...%d)\n", *size);
        return;
    }
    if(empty_bintree(trees[tr])){
        printf("Tree %d is empty\n", tr+1);
    }
    else{
        printf("Tree %d is not empty\n", tr+1);
    }
    return;
}



//AUXILIARY TO INSERT_TREE.
void insert_aux(BinTree **trees, int *size){
    char name[100], course[100];
    int age, tr;

    printf("Type the name of the student: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(name, 100)){
        printf("ERROR: Not valid input or string overflow!\n");
        return;
    }

    printf("Type the course of the student: ");
    fgets(buffer, MAXBUFFER, stdin);
    if(not get_string(course, 100)){
        printf("ERROR: Not valid input or string overflow!\n");
        return;
    }

    if(not write_and_scan("Type the age of the student: ", &age)) return;

    tr = wanted_tree(size);
    if(tr < 0) return;
    if(not insert_bintree(&trees[tr], make_student(age, name, course))){
        printf("ERROR: Not valid tree or no memory available!\n");
        return;
    }
    
    printf("The student was successfully inserted on the tree!\n");
    return;
}



//AUXILIARY TO REMOVE_BINTREE.
void remove_aux(BinTree **trees, int *size){
    int target, tr;
    if(not write_and_scan("Type the age of the student: ", &target)) return;

    tr = wanted_tree(size);
    if(tr < 0) return;
    if(not remove_bintree(&trees[tr], target)){
        printf("Student not found on the tree!\n");
        return;
    }

    printf("The student was successfully removed from the tree!\n");
    return;
}



//AUXILIARY TO SEARCH_BINTREE.
void search_aux(BinTree **trees, int *size){
    int target, ans, tr;
    if(not write_and_scan("Type the age of the student: ", &target)) return;

    tr = wanted_tree(size);
    if(tr < 0) return;
    ans = search_bintree(trees[tr], target);

    if(not ans) printf("The student with age %d is not on the tree!\n");
    else printf("The student with age %d is in the tree!\n");
    return;
}



//AUXILIARY TO SHOW_BINTREE.
void show_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    show_bintree(trees[t]);
    putchar('\n');
    return;
}



//AUXILIARY TO SHOW_ORDERED.
void ordered_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    show_ordered(trees[t]);
    putchar('\n');
    return;
}



//AUXILIARY TO SHOW_TREEVIEW.
void treeview_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    show_treeview(trees[t], 0);
    putchar('\n');
    return;
}



//AUXILIARY TO OLDEST.
void oldest_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    
    Student s = oldest(trees[t]);
    if(s.age == -1){
        printf("There is no students on your tree!\n");
        return;
    }
    printf("The oldest student is %s studying %s, with %d years old!\n", s.name, s.course, s.age);
    return;
}



//AUXILIARY TO PLUS18.
void plus18_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    
    printf("There are %d students who are over 18 years old!\n", plus_18(trees[t]));
    return;
}



//AUXILIARY TO INTERVAL.
void interval_aux(BinTree **trees, int *size){
    int t, a1, a2;
    if(not write_and_scan("Type the minimum age: ", &a1)) return;
    if(not write_and_scan("Type the maximum age: ", &a2)) return;
    
    if(a1 > a2){
        printf("Sorry! [%d,%d] is not a valid interval!\n", a1, a2);
        return;
    }

    t = wanted_tree(size);
    if(t < 0) return;

    printf("There are %d students between ages %d and %d!\n", age_interval(trees[t],a1,a2), a1, a2);
    return;
}



//AUXILIARY TO ONESON.
void oneson_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    
    printf("There are %d nodes with only one son!\n", one_son(trees[t]));
}



//AUXILIARY TO COMPLETE.
void complete_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    int l1, l2;
    l1 = l2 = -1;
    if(complete(trees[t], 0, &l1, &l2)) printf("The tree %d is complete!\n", t+1);
    else printf("The tree %d is not complete!\n", t+1);
    return;
}



//AUXILIARY TO HEIGHT.
void height_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    
    printf("The height of tree %d is %d!\n", t+1, height_bintree(trees[t]));
}



//AUXILIARY TO FREE_BINTREE.
void free_aux(BinTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    free_bintree(&trees[t]);
    (*size)--;
    printf("The tree %d was successfully removed and erased!\n", t+1);

    int i;
    for(i=t; i<*size; i++){
        trees[i] = trees[i+1];
    }
    return;
}



//AUXILIARY T0 MERGE_BINTREE.
void merge_aux(BinTree **trees, int *size){
    int t1, t2;

    if(*size == MAXTREE){
        printf("Sorry! There is no space left!\n");
        return;
    }

    if(not write_and_scan("Type the number of the first tree: ", &t1)) return;
    if(t1 < 1 or t1 > *size){
        printf("Tree not found - type a valid number (1...%d)\n", *size);
        return;
    }

    if(not write_and_scan("Type the number of the second tree: ", &t2)) return;
    if(t2 < 1 or t2 > *size){
        printf("Tree not found - type a valid number (1...%d)\n", *size);
        return;
    }

    printf("MY TREES ARE %d and %d\n", t1-1, t2-1);
    trees[*size] = merge_bintree(trees[t1-1], trees[t2-1]);
    (*size)++;
    printf("The trees %d and %d are now merged on tree %d!\n", t1, t2, *size);
    return;
}



//RETURNS THE WANTED TREE.
int wanted_tree(int *size){
    int tr;

    if(*size == 1) return 0;
    else{
        if(not write_and_scan("Type the number of the wanted tree: ", &tr)) return -1;
        tr--;
        if(tr < 0 or tr >= *size){
            printf("Tree not found - type a valid number (1...%d)\n", *size);
            return -1;
        }
        return tr;
    }
}



//DISPLAYS THE MENU.
int menu(){
    int op;
    while(true){
        system(CLEAR);
        
        printf("[01]. Make a new binary search tree.\n");
        printf("[02]. Verify if a tree is empty.\n");
        printf("[03]. Insert a student on a tree.\n");
        printf("[04]. Remove a student from a tree.\n");
        printf("[05]. Search a student on a tree.\n");
        printf("[06]. Show a tree - in-order\n");
        printf("[07]. Show a tree - ordered\n");
        printf("[08]. Show a tree - treeview\n");
        printf("[09]. Find the oldest student on a tree.\n");
        printf("[10]. Count the 18+ years old students.\n");
        printf("[11]. Count students between two ages.\n");
        printf("[12]. Count the nodes with only one son.\n");
        printf("[13]. Verify if a tree is complete.\n");
        printf("[14]. Get the height of a tree.\n");
        printf("[15]. Merge two trees.\n");
        printf("[16]. Free and erase a tree.\n");
        printf("[17]. Exit\n");

        fgets(buffer, MAXBUFFER, stdin);
        if(not get_int(&op)) printf("Please type a number!\n");
        else if(op < 1 or op > 17) printf("Your number is invalid!\n");
        else return op;

        printf("Press ENTER to try again!\n");
        fgets(buffer, MAXBUFFER, stdin);
    }
}



//FUNCTION TO EXTRACT AN INT FROM A STRING.
int get_int(int *ans){
    if(not ans) return 0;

    int i, j;
    bool tolerance, space;

    i = j = 0;
    if(buffer[i] == '\n' or buffer[i] == '\0') return 0;
    space = false;
    tolerance = true;

    while(buffer[i] != '\0' and buffer[i] != '\n'){
        if(i == MAXBUFFER) return 0;

        if(buffer[i] == ' ' and tolerance){
            i++;
            continue;
        }

        if(buffer[i] == ' ' and not tolerance){
            space = true;
            i++;
            continue;
        }

        else if(space and (buffer[i] >= '0' and buffer[i] <= '9')) return 0;
        else if(buffer[i] < '0' or buffer[i] > '9') return 0;

        tolerance = false;
        buffer[j++] = buffer[i++];
    }
    buffer[j] = '\0';

    int acm = 0;
    for(i=0; i<j; ++i){
        acm += (buffer[i]-'0')*pow(10,j-1-i);
    }
    *ans = acm;
    return 1;
}



//EXTRACTS A STRING FROM THE BUFFER.
int get_string(char *str, int size){
    if(not str or not size) return 0;

    int i, j, notspace;
    i = j = notspace = 0;
    if(buffer[i] == '\n' or buffer[i] == '\0') return 0;

    while(buffer[i] != '\0' and buffer[i] != '\n'){
        if(j >= size) return 0; //OVERFLOW

        if(buffer[i] != ' '){
            str[j] = buffer[i];
            notspace = j;
            ++i;
            ++j;
        }
        else if(buffer[i] == ' ' and not notspace){
            ++i;
        }
    }
    str[notspace+1] = '\0';

    return 1;
}