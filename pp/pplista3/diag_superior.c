#include <stdio.h>
#include <stdlib.h>

double diag_superior(int n, double mat[n][n]);

int main(){
    int n, i, j;
    double med;

    do{
        printf("Digite a dimensao da matriz: ");
        scanf("%d", &n);
        fflush(stdin);
        if(n <= 0 || n > 100) printf("Digite valores validos\n");
        else break;
    }while(1);
    double mat[n][n];

    for(i=0; i<n; ++i){
        for(j=0; j<n; ++j){
            printf("mat[%d][%d] = ", i, j);
            scanf("%lf", &mat[i][j]);
        }
    }

    med = diag_superior(n,mat);
    printf("A media da diagonal superior eh: %.5lf\n", med);
    return 0;
}

double diag_superior(int n, double mat[n][n]){
    int i, j, c = 0;
    double sum = 0.0;
    for(i=0; i<n; ++i){
        for(j=0; j<n; ++j){
            if(j > i && j+i<n-1){
                sum+=mat[i][j];
                ++c;
            }
        }
    }
    return sum/c;
}
