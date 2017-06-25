#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
   int p, n, i, r, ndiv;
   p = 1;
   printf("Digite um numero: ");
   scanf("%d", &n);
   r = sqrt(n);

   if(n == 1 || (n%2 == 0 && n != 2)) p = 0;
   else if(n == 2) p = 1;
   else{
      ndiv = 0;
      for(i = 1; i <= r; i+=2){
         if(n%i == 0) ++ndiv;
         if(ndiv > 1){
            p = 0;
            break;
         }
      }
   }

   if(p) printf("%d eh primo\n", n);
   else printf("%d nao eh primo\n", n);

   return 0;
}
