#include <stdio.h>
#include <stdlib.h>

#define PREC 100

int main(){
   int i;
   double r, n;

   printf("Digite um numero: ");
   scanf("%lf", &n);
   r = n/2;

   for(i = 0; i < PREC; ++i){
      r = 0.5*(r+n/r);
   }
   printf("raiz de %g eh %.10lf\n", n, r);

   return 0;
}
