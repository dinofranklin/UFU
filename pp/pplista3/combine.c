#include <stdio.h>
#include <stdlib.h>

char str[10];

void combine(int n, int k, int par, int init);

int main(){
    int n, k;
    do{
        printf("Digite n e k respectivamente: ");
        scanf("%d %d", &n, &k);
        if(n < 0 || k < 0 || k > n){
            printf("Digite valores validos\n");
        }
        else break;
    }while(1);
    printf("As possiveis combinacoes de 1 a %d com taxa %d sao:\n", n, k);
    str[k] = '\0';
    combine(n, k, 0, 1);
    return 0;
}

void combine(int n, int k, int par, int init){
    int i;
    if(par == k-1){
        for(i = init; i <= n; ++i){
            str[par] = i+'0';
            printf("%s\n", str);
        }
    }
    else{
        for(i = init; i < n; ++i){
            str[par] = i+'0';
            combine(n,k,par+1,i+1);
        }
    }
    return;
}
