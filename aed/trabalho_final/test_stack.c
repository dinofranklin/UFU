//TESTE PARA PILHA

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(){
    int i, n;
    char nm;
    Stack *s = make_stack();
    show_stack(s);
    printf("Type the size: ");
    scanf("%d", &n);
    for(i = 0; i < n; ++i){
        printf("Type the city %d: ", i+1);
        getchar();
        scanf("%c", &nm);
        push(s, nm);
    }
    show_stack(s);
    destroy_stack(s);
    return 0;
}
