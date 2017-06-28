#include <stdio.h>
#include <stdlib.h>

void maxsubmat(int n, int m, int mat[n][m]);

int main(){
    int i, j, n, m;
    printf("Escreva as dimensoes da matriz: ");
    scanf("%d %d", &n, &m);
    int mat[n][m];
    for(i = 0; i < n; ++i){
        for(j = 0; j < m; ++j){
            scanf("%d", &mat[i][j]);
        }
    }
    maxsubmat(n, m, mat);
    return 0;
}

void maxsubmat(int n, int m, int mat[n][m]){
    int i, j, k, l, o, p; //CONTROLE.
    int sum, summax, area;
    int init_i, init_j, fin_i, fin_j; //GUARDA OS PONTOS DA MAIOR MATRIZ. 

    summax = 0;

    for(i = 0; i < n; ++i){
        for(j = 0; j < m; ++j){

            for(k = i; k < n; ++k){
                for(l = j; l < m; ++l){
                    //ANALISA DE (I,J) ATE (K,L).

                    //FAZ A SOMA DO INTERVALO (I,J) ATE (K,L).
                    sum = 0;
                    for(o = i; o <= k; ++o){
                        for(p = j; p <= l; ++p){
                            sum += mat[o][p];
                        }
                    }

                    area = (k-i+1)*(l-j+1);
                    //printf("Soma de (%d,%d) ate (%d,%d) = %d e Area = %d\n",i,j,k,l,sum,area);

                    //SE A SOMA EH IGUAL A AREA ACHAMOS UMA MATRIZ COMPLETA.
                    if(area == sum && sum > summax){
                        init_i = i;
                        init_j = j;
                        fin_i = k;
                        fin_j = l;
                        summax = sum;
                    }

                }
            }
        }
    }

    printf("A maior submatriz completa esta em (%d,%d) ate (%d,%d):\n\n", init_i, init_j, fin_i, fin_j);

    for(i = init_i; i <= fin_i; ++i){
        for(j = init_j; j <= fin_j; ++j){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    return;
}