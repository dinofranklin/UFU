#include <stdio.h>
#include <stdlib.h>

int main(){
   int n, spc, i, j;

   printf("Digite a altura da piramide: ");
   scanf("%d", &n);

   spc = n - 1;
   for(i = 0; i < n; ++i){
      for(j = 0; j < spc; ++j) printf("  ");
      if(!i) printf("1");
      else{
         for(j = 1; j <= i+1; ++j) printf("%d ", j);
         for(j = i; j > 0; --j) printf("%d ", j);
      }
      printf("\n");
      --spc;
   }
   return 0;
}
