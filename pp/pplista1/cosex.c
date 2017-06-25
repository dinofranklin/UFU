#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.141592

int main(){
   double g, x, c, f, i;
   int fg;

   printf("Digite x em graus: ");
   scanf("%lf", &g);
   x = pi*g/180.0;

   fg = 0;
   c = f = 1.0;
   for(i = 2.0; i <= 20; i += 2.0){
      f *= i*(i-1.0);
      if(fg) c += pow(x,i)/f;
      else c -= pow(x,i)/f;
      fg ^= 1;
   }
   printf("cos(%g) = %.10lf\n", g, c);
   return 0;
}
