#include <stdio.h>
#include <stdlib.h>

void telhado(int n, int mat[n][n]);

int main(){
    int i, j, n;
    do{
        printf("Digite a dimensao da matriz: ");
        scanf("%d", &n);
        fflush(stdin);
        if(n <= 0 || n > 100 || n%2 == 0) printf("Digite valores validos\n");
        else break;
    }while(1);

    int mat[n][n];
    telhado(n, mat);
    for(i = 0; i < n; i++){
        for(j = 0; j < n; ++j){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void telhado(int n, int mat[n][n]){
    int i, j;

    for(i = 0; i < n; ++i){
        for(j = 0; j < n; ++j){

            if((i<=n/2 && j<=n/2) || (i>n/2 && j>n/2)){
                mat[i][j] = abs(i-j);
            }
            else{
                mat[i][j] = abs(n-i-j-1);
            }
        }
    }
    return;
}
