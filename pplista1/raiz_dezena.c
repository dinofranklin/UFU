#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN 1000
#define MAX 9999

int main(){
   int n, ds;
   double r;
   printf("Numeros cuja raiz quadrada eh a soma das dezenas: \n");
   for(n = MIN; n <= MAX; ++n){
      ds = n%100 + n/100;
      r = sqrt(n);
      if(ds == r) printf("%d\n", n);
   }
   return 0;
}
