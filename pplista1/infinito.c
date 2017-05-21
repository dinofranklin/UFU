#include <stdio.h>
#include <stdlib.h>

int main(){
   int i, j, n;

   printf("n? ");
   scanf("%d", &n);

   for(i = 0; i < n; ++i){
      for(j = 0; j < 3*n; ++j){

         if(i+j == n-1 && i < n/2) printf(" ");
         else if(i == j && i >= n/2) printf(" ");

         else if(j-i == n && j >= n) printf(" ");
         else if(j+i == 2*n-1 && j >= n) printf(" ");

         else if(i+j == 3*n-1 && i >= n/2) printf(" ");
         else if(j-i == 2*n && i < n/2) printf(" ");

         else printf("%c", 0xC5);
      }
      printf("\n");
   }

   return 0;
}
