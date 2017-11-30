#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gentree.h"

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

char buffer[1000];

//FUNCTION DECLARATIONS.
int menu();
int get_int(int *ans);
void make_aux(GenTree **t);
void search_aux(GenTree *t);
void height_aux(GenTree *t);
void insertson_aux(GenTree *t);
void insertfather_aux(GenTree **t);
void insertnode_aux(GenTree *t);
void remove_aux(GenTree **t);
void leaf_aux(GenTree *t);
void heightnode_aux(GenTree *t);
void preorder_aux(GenTree *t);
void postorder_aux(GenTree *t);
void level_aux(GenTree *t);
void degree_aux(GenTree *t);
void nodes_aux(GenTree *t);


int main(){
    int op;
    GenTree *t = NULL;

    while(true){
        op = menu();
        if(op == 1) make_aux(&t);
        else if(op == 2) insertson_aux(t);
        else if(op == 3) insertfather_aux(&t);
        else if(op == 4) insertnode_aux(t); 
        else if(op == 5) remove_aux(&t);
        else if(op == 6) show_gentree(t);
        else if(op == 7) search_aux(t);
        else if(op == 8) height_aux(t);
        else if(op == 9) preorder_aux(t);
        else if(op == 10) postorder_aux(t);
        else if(op == 11) level_aux(t);
        else if(op == 12) leaf_aux(t);
        else if(op == 13) degree_aux(t);
        else if(op == 14) nodes_aux(t);
        else if(op == 15) heightnode_aux(t);
        else if(op == 16) free_gentree(&t);
        else if(op == 17) print_treeview(t, 0);
        else if(op == 18) break;
        else printf("ERROR: Something went terribly wrong!\n");

        printf("\nPress ENTER to go back to the menu!\n");
        fgets(buffer, 1000, stdin);
    }
    
    printf("Goodbye...\n");
    return 0;
}



//AUXILIARY FUNCTION TO MAKE A GENERIC TREE.
void make_aux(GenTree **t){
    int value;
    printf("Type the value of the root node: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    *t = make_gentree(value);
    if(not t){
        printf("ERROR: No memory available!\n");
        return;
    }
    printf("Sucess! Your tree has been created!\n");
    return;
}



//AUXILIARY FUNCTION TO SEARCH_GENTREE.
void search_aux(GenTree *t){
    int value;
    printf("Type the value you want to search: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    if(search_gentree(t, value)){
        printf("The value %d is in the tree!\n", value);
    }
    else{
        printf("The value %d is not in the tree!\n", value);
    }
    return;
}



//AUXILIARY FUNCTION TO HEIGHT_GENTREE.
void height_aux(GenTree *t){
    printf("The height of your tree is %d\n", height_gentree(t));
    return;
}



//AUXILIARY FUNCTION TO INSERTSON_GENTREE.
void insertson_aux(GenTree *t){
    int value, ret;
    printf("Type the value to insert as son of you generic tree: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    GenTree *new = make_gentree(value);
    if(not new){
        printf("ERROR: No memory available!\n");
        return;
    }

    ret = insertson_gentree(t,new);
    if(not ret or ret == -1){
        printf("ERROR: Invalid tree(s) on insertion!\n");
        free_gentree(&new);
        return;
    }
    printf("Success! Your node was inserted!\n");
    return;
}



//AUXILIARY FUNCTION TO REMOVE_GENTREE.
void remove_aux(GenTree **t){
    int value;
    printf("Type the value you want to remove from your tree: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }
    
    if(not remove_gentree(t, value)){
        printf("The value %d was not found in your tree\n", value);
        return;
    }
    printf("Success! The tree with root value %d was removed!\n", value);
    return;
}



//AUXILIARY FUNCTION TO INSERTFATHER_GENTREE.
void insertfather_aux(GenTree **t){
    int value, ret;
    printf("Type the value to insert as father of your generic tree: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    GenTree *new = make_gentree(value);
    if(not new){
        printf("ERROR: No memory available!\n");
        return;
    }

    ret = insertfather_gentree(t,new);
    if(not ret or ret == -1){
        printf("ERROR: Invalid tree(s) on insertion!\n");
        free_gentree(&new);
        return;
    }
    printf("Success! Your node was inserted!\n");
    return;
}



//AUXILIARY FUNCTION TO INSERTNODE_GENTREE.
void insertnode_aux(GenTree *t){
    int value, ret;
    printf("Type the value to insert in your generic tree: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    GenTree *new = make_gentree(value);
    if(not new){
        printf("ERROR: No memory available!\n");
        return;
    }

    printf("Type the value you want to be the father of node %d: ", value);
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    ret = insertnode_gentree(t,new,value);
    if(not ret or ret == -1){
        printf("ERROR: Invalid tree(s) on insertion!\n");
        free_gentree(&new);
        return;
    }
    printf("Success! Your node was inserted!\n");
    return;
}



//AUXILIARY FUNCTION TO LEAFS.
void leaf_aux(GenTree *t){
    int leaf;
    leaf = leafs(t);
    if(not leaf) printf("ERROR: Invalid tree!\n");
    else printf("Your tree has %d leaf nodes\n", leaf);
    return;
}



//AUXILIARY FUNCTION TO NODE_HEIGHT
void heightnode_aux(GenTree *t){
    int hei, value;
    printf("Type the value of the node you want to know the height: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }
    
    hei = node_height(t, value);
    if(hei == -1) printf("ERROR: Value not found in tree!\n");
    else printf("The height of node %d is %d\n", value, hei);
    return;
}



//AUXILIARY FUNCTION TO PREORDER.
void preorder_aux(GenTree *t){
    printf("Your tree in preorder: \n");
    pre_order(t);
    putchar('\n');
    return;
}



//AUXILIARY FUNCTION TO POSTORDER.
void postorder_aux(GenTree *t){
    printf("Your tree in postorder: \n");
    post_order(t);
    putchar('\n');
    return;
}



//AUXILIARY FUNCTION TO TRAVERSE LEVEL.
void level_aux(GenTree *t){
    printf("Your tree traversed by level:\n");
    traverse_level(t);
    putchar('\n');
    return;
}



//AUXILIARY FUNCTION TO DEGREE.
void degree_aux(GenTree *t){
    int deg = gentree_degree(t);
    if(deg == -1){
        printf("ERROR: Not a valid tree!\n");
        return;
    }
    printf("The degree of your tree is: %d\n", deg);
    return;
}



//AUXILIARY FUNCTION TO NODES.
void nodes_aux(GenTree *t){
    int nds, value;
    printf("Type the value of the degree: ");
    fgets(buffer, 1000, stdin);
    if(not get_int(&value)){
        printf("ERROR: Not valid input!\n");
        return;
    }

    nds = nodes(t, value);
    if(nds == -1){
        printf("ERROR: Degree not found or invalid tree!\n");
        return;
    }
    printf("The number of nodes of the tree with degree %d is %d", value, nds);
    return;
}


//DYSPLAYS THE MENU.
int menu(){
    int op;
    while(true){
        system(CLEAR);
        printf("O que deseja fazer? \n");
        printf("[01]. Make a generic tree\n");
        printf("[02]. Insert a new node as son of a generic tree\n");
        printf("[03]. Insert a new node as parent of your generic tree\n");
        printf("[04]. Insert a new node as son of a given node\n");
        printf("[05]. Remove a node from a generic tree\n");
        printf("[06]. Print the generic tree\n");
        printf("[07]. Search a element in a generic tree\n");
        printf("[08]. Find the height of a generic tree\n");
        printf("[09]. Traverse the tree in preorder\n");
        printf("[10]. Traverse the tree in postorder\n");
        printf("[11]. Traverse the tree by level (BFS)\n");
        printf("[12]. Find the number of leafs\n");
        printf("[13]. Find the degree of a generic tree\n");
        printf("[14]. Find the number of nodes of a tree of given degree\n");
        printf("[15]. Find the height of a node\n");
        printf("[16]. Free your generic tree\n");
        printf("[17]. Print treeview\n");
        printf("[18]. Exit\n");

        fgets(buffer, 1000, stdin);
        if(not get_int(&op)) printf("Only numbers are accepted!\n");
        else if(op < 1 or op > 18) printf("Your number is not valid!\n");
        else return op;
        
        printf("Press ENTER to try again!\n");
        fgets(buffer, 1000, stdin);
    }
}



//FUNCTION TO EXTRACT AN INT FROM A STRING.
int get_int(int *ans){
    if(not ans) return 0;

    int i, j, len;
    bool tolerance, space;

    i = j = 0;
    if(buffer[i] == '\n' or buffer[i] == '\0') return 0;
    space = false;
    tolerance = true;

    while(buffer[i] != '\0' and buffer[i] != '\n'){
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
