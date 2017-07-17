//TESTE PARA LISTA

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
    int i, j, n, a, b;
    char c;
    List **l = make_lists();
    show_lists(l);
    for(i = 0; i < LSIZE; ++i){
        printf("How many cities for %c: ", i+'A');
        scanf("%d", &n);
        for(j = 0; j < n; ++j){
            printf("Type city %d: ", j+1);
            getchar();
            scanf("%c", &c);
            add_city(l[i], c);
        }
    }
    show_lists(l);
    printf("How many querys: ");
    scanf("%d", &n);
    for(i = 0; i < n; ++i){
        printf("Type list number and position: ");
        scanf("%d %d", &a, &b);
        printf("List %d at %d is %c\n", a, b, list_position(l[a], b));
    }
    destroy_lists(l);
    return 0;
}
