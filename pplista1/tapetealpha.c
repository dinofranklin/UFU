#include <stdio.h>
#include <stdlib.h>

int main(){
   int i, j, n, min;

   printf("Numero de caracteres: ");
   scanf("%d", &n);

   for(i = 0; i < 2*n; ++i){
      for(j = 0; j < 2*n; ++j){
         min = i;
         if(j < min) min = j;
         if(2*n - i - 1 < min) min = 2*n-i-1;
         if(2*n - j - 1 < min) min = 2*n-j-1;
         printf("%c", 'A'+min);
      }
      printf("\n");
   }

   return 0;
}
