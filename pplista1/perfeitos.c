#include <stdio.h>
#include <stdlib.h>

#define MAX 200

int main(){
   int p, a, r, i, j, sdiv;
   p = a = r = 0;

   for(i = 1; i <= MAX; ++i){
      sdiv = 0; // Soma dos divisores de i inicialmente é zero.
      for(j = 1; j <= i/2; ++j){
         if(i%j == 0) sdiv += j; // Cada divisor é somado a sdiv.
      }
      if(sdiv == i){ //Verifica se i é um número perfeito.
         ++p;
         printf("%d: perfeito\n", i);
      }
      else if(sdiv < i){ //Senão verifica se i é um número reduzido.
         ++r;
         printf("%d: reduzido\n", i);
      }
      else{ //Do contrário i só pode ser um número abundante.
         ++a;
         printf("%d: abundante\n", i);
      }
   }
   printf("Total de numeros perfeitos: %d\n", p);
   printf("Total de numeros reduzidos: %d\n", r);
   printf("Total de numeros abundantes: %d\n", a);
   return 0;
}
