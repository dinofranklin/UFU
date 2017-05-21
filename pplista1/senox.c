#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.141592

int main(){
   double g, x, s, f, i;
   int flag;

   printf("Digite x em graus: ");
   scanf("%lf", &g);
   x = pi*g/180.0;

   s = x;
   flag = 0;
   f = 1.0;
   for(i = 3.0; i <= 19; i += 2.0){
      f *= i*(i-1.0);
      if(flag) s += pow(x,i)/f;
      else s -= pow(x,i)/f;
      flag ^= 1;
   }
   printf("sin(%g) = %.10lf\n", g, s);
   return 0;
}
