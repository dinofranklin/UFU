#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "avltree.h"

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
#define MAXTREE 5
#define MAXBUFFER 1000

char buffer[MAXBUFFER];

//FUNCTION DECLARATIONS.
int menu();
int get_int(int *ans);
int write_and_scan(char *msg, int *ans);
int get_string(char *str, int size);
int wanted_tree(int *size);

//AUXILIARY FUNCTIONS.
void make_aux(AvlTree **trees, int *size);
void empty_aux(AvlTree **trees, int *size);
void insert_aux(AvlTree **trees, int *size);
void remove_aux(AvlTree **trees, int *size);
void show_aux(AvlTree **trees, int *size);
void ordered_aux(AvlTree **trees, int *size);
void treeview_aux(AvlTree **trees, int *size);
void search_aux(AvlTree **trees, int *size);
void free_aux(AvlTree **trees, int *size);
void traffic_aux(AvlTree **trees, int *size);
void idle_aux(AvlTree **trees, int *size);
void internal_aux(AvlTree **trees, int *size);
void full_aux(AvlTree **trees, int *size);
void level_aux(AvlTree **trees, int *size);
void equal_aux(AvlTree **trees, int *size);


int main(){
    int op, size = 0;
    AvlTree **trees = (AvlTree **) malloc(MAXTREE*sizeof(AvlTree *));

    while(true){
        op = menu();

        if(op == 1) make_aux(trees, &size);
        else if(op ==  2) insert_aux(trees, &size);
        else if(op ==  3) remove_aux(trees, &size);
        else if(op ==  4) empty_aux(trees, &size);
        else if(op ==  5) search_aux(trees, &size);
        else if(op ==  6) show_aux(trees, &size);
        else if(op ==  7) ordered_aux(trees, &size);
        else if(op ==  8) treeview_aux(trees, &size);
        else if(op ==  9) traffic_aux(trees, &size);
        else if(op == 10) idle_aux(trees, &size);
        else if(op == 11) internal_aux(trees, &size);
        else if(op == 12) full_aux(trees, &size);
        else if(op == 13) level_aux(trees, &size);
        else if(op == 14) equal_aux(trees, &size);
        else if(op == 15) free_aux(trees, &size);
        else if(op == 16) break;
        else printf("ERROR: Something went terribly wrong!\n");

        printf("Press ENTER to go back to the menu!\n");
        fgets(buffer, MAXBUFFER, stdin);
    }

    return 0;
}



//AUXILIRAY TO .
void make_aux(AvlTree **trees, int *size){
    if(*size == MAXTREE){
        printf("Sorry! You cant have more than %d trees!\n", *size);
        return;
    }
    trees[*size] = make_avltree();
    ++(*size);
    printf("Tree number %d was created!\n", *size);
    return;
}



//AUXILIRAY TO EMPTYAVL.
void empty_aux(AvlTree **trees, int *size){
    if(*size == 0){
        printf("You don't any trees, try to create some!\n");
        return;
    }

    int t;
    t = wanted_tree(size);
    if(t < 0) return;

    if(empty_avltree(trees[t])){
        printf("Tree %d is empty\n", t+1);
    }
    else{
        printf("Tree %d is not empty\n", t+1);
    }
    return;
}



//AUXILIRAY TO INSERT_AVL.
void insert_aux(AvlTree **trees, int *size){
    char location[100];
    int id, traffic, capacity, t;

    if(not write_and_scan("Type the id of the node: ", &id)) return;
    if(not write_and_scan("Type the traffic of the node: ", &traffic)) return;
    if(not write_and_scan("Type the capacity of the node: ", &capacity)) return;

    printf("Type the location of the node: ");
    fgets(buffer, 1000, stdin);
    if(not get_string(location, 100)){
        printf("ERROR: Not valid input or string overflow!\n");
        return;
    }
    
    t = wanted_tree(size);
    if(t < 0) return;
    if(not insert_avl(&trees[t], make_node(id,traffic,capacity, location))){
        printf("ERROR: Not valid tree or no memory available!\n");
        return;
    }
    
    printf("The student was successfully inserted on the tree!\n");
    return;
}



//AUXILIRAY TO REMOVE_AVL.
void remove_aux(AvlTree **trees, int *size){
    int target, t;
    if(not write_and_scan("Type the traffic of the node: ", &target)) return;

    t = wanted_tree(size);
    if(t < 0) return;
    if(not remove_avl(&trees[t], target)){
        printf("Node not found on the tree!\n");
        return;
    }

    printf("The node was successfully removed from the tree!\n");
    return;
}



//AUXILIRAY TO SHOW_AVL.
void show_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    show_avl(trees[t]);
    putchar('\n');
    return;
}



//AUXILIRAY TO ORDERED_AVL.
void ordered_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    ordered_avl(trees[t]);
    putchar('\n');
    return;
}



//AUXILIRAY TO TREEVIEW.
void treeview_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;
    treeview_avl(trees[t], 0);
    putchar('\n');
    return;
}



//AUXILIRAY TO SEARCH.;
void search_aux(AvlTree **trees, int *size){
    int target, ans, t;
    if(not write_and_scan("Type the traffic of the node: ", &target)) return;

    t = wanted_tree(size);
    if(t < 0) return;
    ans = search_avltree(trees[t], target);

    if(not ans) printf("The node with traffic %d is not on the tree!\n", target);
    else printf("The node with traffic %d is in the tree!\n", target);
    return;
}



//AUXILIRAY TO FREE_AVL.
void free_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    free_avl(&trees[t]);
    (*size)--;
    printf("The tree %d was successfully removed and erased!\n", t+1);

    int i;
    for(i=t; i<*size; i++){
        trees[i] = trees[i+1];
    }
    return;
}



//AUXILIRAY TO LEAST_TRAFFIC.
void traffic_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    if(empty_avltree(trees[t])){
        printf("Sorry! There are no nodes in the tree!\n");
        return;
    }
    printf("The node with least traffic is ");
    print_node( least_traffic(trees[t]) );
    return;
}



//AUXILIRAY TO COUNT_IDLE.
void idle_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    printf("There are %d idle nodes in the tree!\n", count_idle(trees[t]));
    return;
}



//AUXILIRAY TO COUNT_INTERNAL.
void internal_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    printf("There are %d internal nodes in the tree!\n", count_internal(trees[t]));
    return;
}



//AUXILIRAY TO FULL.;
void full_aux(AvlTree **trees, int *size){
    int t = wanted_tree(size);
    if(t < 0) return;

    if(full(trees[t])){
        printf("Tree %d is full!\n", t+1);
    }
    else{
        printf("Tree %d is not full!\n", t+1);
    }
    return;
}   



//AUXILIRAY TO LEVEL_OF.
void level_aux(AvlTree **trees, int *size){
    char location[100];
    int id, traffic, capacity, t, ans;

    if(not write_and_scan("Type the id of the node: ", &id)) return;
    if(not write_and_scan("Type the traffic of the node: ", &traffic)) return;
    if(not write_and_scan("Type the capacity of the node: ", &capacity)) return;

    printf("Type the location of the node: ");
    fgets(buffer, 1000, stdin);
    if(not get_string(location, 100)){
        printf("ERROR: Not valid input or string overflow!\n");
        return;
    }
    
    t = wanted_tree(size);
    if(t < 0) return;

    ans = level_of(trees[t], make_node(id,traffic,capacity,location));
    if(ans == -1){
        printf("Node not found in the tree!\n");
        return;
    }
    printf("The level of your node %d with traffic %d is %d\n", id, traffic, ans);
    return;
}



//AUXILIRAY TO EQUAL_AVL.
void equal_aux(AvlTree **trees, int *size){
    int t1, t2;

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

    if(equal_avl(trees[t1-1], trees[t2-1])){
        printf("Trees %d and %d are equal.\n", t1-1, t2-1);
        return;
    }
    printf("Trees %d and %d are not equal.\n", t1-1, t2-1);
    return;
}



//DISPLAYS THE MENU.
int menu(){
    int op;
    while(true){
        system(CLEAR);

        printf("[01]. Make a new avl tree.\n");
        printf("[02]. Insert a new element on your tree.\n");
        printf("[03]. Remove a element from your tree.\n");
        printf("[04]. Verify if your tree is emtpy.\n");
        printf("[05]. Search for an element in the tree.\n");
        printf("[06]. Show AVL tree - Notation.\n");
        printf("[07]. Show AVL tree - Ordered.\n");
        printf("[08]. Show AVL tree - Treeview.\n");
        printf("[09]. Find the node with least traffic.\n");
        printf("[10]. Count the idle nodes.\n");
        printf("[11]. Count the internal nodes (derivation).\n");
        printf("[12]. Check if your tree is full.\n");
        printf("[13]. Get the level of a node.\n");
        printf("[14]. Check if two trees are equal.\n");
        printf("[15]. Free and erase your tree.\n");
        printf("[16]. Exit.\n");

        fgets(buffer, MAXBUFFER, stdin);
        if(not get_int(&op)) printf("Please type a number!\n");
        else if(op < 1 or op > 16) printf("Your number is invalid!\n");
        else return op;

        printf("Press ENTER to try again!\n");
        fgets(buffer, MAXBUFFER, stdin);
    }
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
