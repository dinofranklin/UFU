#include <stdio.h>
#include <stdlib.h>

#define PREC 0.00001

int main(){
   double pi, t, i;
   int fg;

   pi = i = 1.0;
   fg = 0;
   while(i += 2){
      t = 1/i;
      if(t < PREC) break;
      if(fg) pi += t;
      else pi -= t;
      fg ^= 1;
   }
   pi *= 4;
   printf("pi = %.6lf\n", pi);
   return 0;
}
