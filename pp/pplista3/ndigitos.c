#include <stdio.h>
#include <stdlib.h>

int ndigitos(int n);

int main(){
    int n;
    printf("Digite um numero: ");
    scanf("%d", &n);
    printf("Numero de digitos de %d eh %d\n", n, ndigitos(n));
    return 0;
}

int ndigitos(int n){
    if(n == 0) return 0;
    else return 1 + ndigitos(n/10);
}
