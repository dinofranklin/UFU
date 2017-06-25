#include <stdio.h>
#include <stdlib.h>

int main(){
   int m, n, x, y, si;
   si = 0;

   do{
      printf("Digite x e y inteiros: ");
      scanf("%d %d", &m, &n);
   }while(m <= 0 || n <= 0);
   x = m;
   y = n;

   while(x != 0){
      if(x%2 != 0) si += y;
      y = y * 2;
      x = x/2;
   }
   printf("%d*%d = %d\n", m, n, si);

   return 0;
}
