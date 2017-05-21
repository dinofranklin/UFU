#include <stdio.h>
#include <stdlib.h>

int main(){
   int n, i, j, x;

   printf("Digite um numero: ");
   scanf("%d", &n);

   x = 1;
   for(i = 0; i < n; ++i){
      for(j = 0; j <= i; ++j) printf("%02d ", x++);
      printf("\n");
   }

   return 0;
}
