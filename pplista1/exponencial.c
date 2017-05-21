#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PREC 0.0000001

int main(){
   double r, t, f, x, i;

   printf("Informe x: ");
   scanf("%lf", &x);

   r = f = i = 1.0L;
   while(1){
      t = pow(x,i)/f;
      if(t < PREC) break;
      r += t;
      ++i;
      f = i * f;
   }
   printf("e^%g = %.7lf\n", x, r);

   return 0;
}
